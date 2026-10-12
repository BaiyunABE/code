# Memory Allocator Implementation

This project implements a custom memory allocator (`mm_malloc` and `mm_free`) and demonstrates its usage with a binary search tree.

## Project Structure

- `main.c`: Contains the main program that uses the memory allocator to manage a binary search tree.
- `mm_malloc.c`: Implementation of the custom memory allocator.
- `mm_malloc.h`: Header file for the memory allocator.
- `Makefile`: Builds the project.

## Features

### Memory Allocator
- **Best-fit allocation strategy**: Finds the smallest suitable free block.
- **Block splitting**: Splits blocks if remaining space is above a threshold (`MIN_FREE_BLOCK_SIZE`).
- **Coalescing**: Merges adjacent free blocks during `mm_free`.
- **Debugging**: Includes a `print()` function to inspect memory state.

### Binary Search Tree
- **Insertion**: Adds nodes while maintaining BST properties.
- **In-order traversal**: Prints tree contents in sorted order.
- **Destruction**: Frees all allocated memory.

## Build and Run

1. **Build the project**:
   ```bash
   make
   ```

2. **Run the executable**:
   ```bash
   ./main
   ```

3. **Clean up**:
   ```bash
   make clean
   ```

## Output Explanation

The program outputs:
- Tree contents after each insertion (in-order traversal).
- Memory state after each operation via `print()`, showing:
  - Free list head pointer.
  - Hex dump of the first 256 bytes of memory.

## Key Functions

- `init()`: Initializes the memory buffer.
- `mm_malloc(size_t size)`: Allocates memory.
- `mm_free(void *ptr)`: Frees allocated memory.
- `insert()`: Adds nodes to the BST.
- `print_tree()`: Prints BST contents.
- `destroy()`: Frees the entire BST.

## Memory Management Details

- **Buffer size**: 4096 bytes.
- **Minimum free block size**: 32 bytes.
- **Alignment**: 16-byte boundaries.
- **Magic number**: Used to detect invalid frees.

## Notes

- The allocator is designed for demonstration purposes and may not handle all edge cases.
- For production use, consider more robust error handling and optimizations.

