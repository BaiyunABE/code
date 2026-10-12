# File System

## Intro

Use VSFS(Very Simple File System) as an example.

Pay attention to:
- Data structure
- Access method

## Context

Block size: `4KB`
Block number: `64`

```text
 0             7
+-+-+-+---------+
|S|i|d|    I    |
+-+-+-+---------+
\               \
\       D       \
\               \
+---------------+
```

- `S`: Super block. Record some information of file system.
- `i`: Inode bitmap. Record whether a byte of inode table is allocated.
- `d`: Data bitmap. Record whether a byte of data region is allocated.
- `I`: Inode table. Record inode, information of each file.
- `D`: Data region. Record data.

## Inode

Inode size: `256B`
Inode number: `80`

```text
0    2    4    6    8
+----+----+----+----+
|type|size|blks|lnks|
+----+----+----+----+
\                   \
\     block(14)     \
\                   \
+-------------------+
```

## Indirect Pointer

## Directory

```text
inum | reclen | strlen | name
  5       4        2     .
  2       4        3     ..
 12       4        4     foo
 13       4        4     bar
 24       8        7     foobar
```

## Free Space Management

- use bit map

## Read and Write

## Cache
