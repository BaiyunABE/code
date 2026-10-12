#include "vsfs.h"
#include "bio.h"

#include <stdint.h>
#include <string.h>

#define SBSTART 0
#define IBSTART 1
#define DBSTART 2
#define MAGIC 0xDEADBEEF
#define DBLKS 56
#define IBLKS 80
#define ISTART 3
#define DSTART 8

#define F_FILE 0
#define F_DIR 1

typedef struct {
  uint32_t magic;
  uint32_t blocks;
  uint32_t inode_blocks;
  uint32_t inode_start;
  uint8_t padding[4080];
} vsfs_sb_t;

typedef struct {
  uint16_t type;
  uint16_t size;
  uint16_t blks;
  uint16_t lnks;
  uint16_t block[12];
} vsfs_inode_t;

void ialloc_init()
{
  char inode_bit_map[BLK_SIZE];
  memset(inode_bit_map, 0, BLK_SIZE);
  bio_write(IBSTART, inode_bit_map);
}

void dalloc_init()
{
  char data_bit_map[BLK_SIZE];
  memset(data_bit_map, 0, BLK_SIZE);
  bio_write(DBSTART, data_bit_map);
}


void vsfs_init()
{
  // init bio
  bio_init();

  // read superblock
  vsfs_sb_t superblock;
  bio_read(SBSTART, &superblock);
  if (superblock.magic == MAGIC) {
    return;
  }

  // create superblock
  memset(&superblock, 0, BLK_SIZE);
  superblock.magic = MAGIC;
  superblock.blocks = DBLKS;
  superblock.inode_blocks = IBLKS;
  superblock.inode_start = ISTART;
  bio_write(SBSTART, &superblock);

  // create inode bit map
  ialloc_init();

  // create data bit map
  dalloc_init();

  // create root directory
}

int ialloc()
{
  char buf[BLK_SIZE];
  bio_read(IBSTART, buf);
  for (int i = 0; i < BLK_SIZE; i++) {
    if (buf[i] == 0) {
      buf[i] = 1;
      bio_write(IBSTART, buf, BLK_SIZE);
      return i;
    }
  }
  return -1; // overflow
}

int dalloc()
{
  char buf[BLK_SIZE];
  bio_read(DBSTART, buf);
  for (int i = 0; i < BLK_SIZE; i++) {
    if (buf[i] == 0) {
      buf[i] = 1;
      bio_write(DBSTART, buf, BLK_SIZE);
      return i;
    }
  }
  return -1; // overflow
}

void vsfs_create(char* filename)
{
  int inum = ialloc();
  vsfs_inode_t inode;
  memset(&inode, 0, sizeof(inode));
  inode.type = F_FILE;
  inode.size = 0;
  inode.blks = 1;
  inode.lnks = 1;
  inode.block[0] = dalloc();
  bio_write(inum, &inode);
}
