#ifndef _BIO_H_
#define _BIO_H_
#define BLK_SIZE 4096
void bio_init();
void bio_read(int blocks, void* buf, int num);
void bio_write(int blocks, void* buf, int num);
#endif // !_BIO_H_
