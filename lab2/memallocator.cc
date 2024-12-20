#include "memallocator.h"

#include <stddef.h>
#include <stdbool.h>

#include <stdio.h>


// A structure to store metadata of memory block
struct MemoryBlock {
	int f_size;
	int p_size;
};

typedef struct MemoryBlock MemoryBlock;

// Creating global variables
MemoryBlock* _memory_pool;
int _pool_size; // Number of memory blocks

// Return minimum size in bytes of the memory pool to allocate 0-bytes block
int memgetminimumsize() {
	return (int)sizeof(MemoryBlock);
};


// Returns size in bytes of additional information per allocation
int memgetblocksize() {
	return (int)sizeof(MemoryBlock);
};

// We don't need to store pointer to next element because it's: [pointer to next block] = [pointer to current block] + size
// We need a 'free' flag for each memory block instead of using 'bool' (as it is 8 BYTES LONG!), we will use the first bit 
// in f_size field, therefore the maximum size of allocated memory will be 2^31 = 2 147 483 648 bytes
// Also to reduce memory cost, instead of using pointer to the previous block which is 8 bytes long, we'll storage previous
// block size (only for 4 bytes), so the pointer to the previous block we'll be: [pointer to previous block] = [pointer to current block] - p_size

// FINALLY: We store only sizes of current and previous blocks and freedom flag.
// A size of metadata for each memory block is only 8 bytes


// Getters for MemoryBlock

// Size of current memory block
static int _size(MemoryBlock* mblock) {
	// Remove 1st bit as it is a freedom flag
	return mblock->f_size & 0x7FFFFFFF;
}

// Freedom flag of current memory block
static bool _free(MemoryBlock* mblock) {
	return (bool)(mblock->f_size >> 31);
}

// Pointer to memory from current block
static void* _data(MemoryBlock* mblock) {
	return (void*)((char*)mblock + sizeof(MemoryBlock));
}

// Pointer to next element
static MemoryBlock* _next(MemoryBlock* mblock) {
	MemoryBlock* next = (MemoryBlock*)((char*)mblock + _size(mblock) + sizeof(MemoryBlock));
	return ((char*)next < (char*)_memory_pool + _pool_size) ? next : 0;
}

// Pointer to previous element
static MemoryBlock* _prev(MemoryBlock* mblock) {
	return mblock->p_size ? (MemoryBlock*)((char*)mblock - mblock->p_size - sizeof(MemoryBlock)) : 0;
}


// Setters for MemoryBlock

// Setter for current block size
static void s_size(MemoryBlock* mblock, int size) {
	mblock->f_size = (mblock->f_size & 0x80000000) | (size & 0x7FFFFFFF);
}

// Set previous block pointer (p_size)
static void s_prev(MemoryBlock* mblock, MemoryBlock* prev) {
	mblock->p_size = prev ? _size(prev) : NULL;
}

// Set freedom flag
static void s_free(MemoryBlock* mblock, bool flag) {
	mblock->f_size = flag ? (mblock->f_size | 0x80000000) : (mblock->f_size & 0x7FFFFFFF);
}


// Init memory system with memory block pMemory.
int meminit(void* pMemory, int size) {
	if (!pMemory || size < sizeof(MemoryBlock))
		return 0;

	_memory_pool = (MemoryBlock*)pMemory;
	_pool_size = size;

	s_size(_memory_pool, size - sizeof(MemoryBlock));
	s_free(_memory_pool, true);
	s_prev(_memory_pool, NULL);

	return 0;
};

// You can implement memory leak checks here
void memdone() {
	_memory_pool = NULL;
	_pool_size = 0;
};

// Allocate memory block of size 'size'.
// Returns pointer to memory block if success, 0 otherwise
void* memalloc(int size) {
	if (size <= 0 || !_memory_pool)
		return 0;

	MemoryBlock* mblock = _memory_pool;
	MemoryBlock* check_block = NULL; // Block to get memory from
	int counter = 2;

	// Going through all memory blocks
	while (mblock != NULL) {
		if (_size(mblock) >= size && _free(mblock) && counter > 0) {
			check_block = mblock;

			counter--;

			if (!counter) // Looking for block untill counter == 0
				break;
		}

		mblock = _next(mblock);
	}

	// Check if we've not found a valid memory block
	if (check_block == NULL)
		return 0;

	// Otherwise allocating memory from this block
	mblock = check_block;
	s_free(mblock, false);

	// If not ehough memory to make more blocks
	if (_size(mblock) <= size + sizeof(MemoryBlock))
		return _data(mblock);

	// If enough memory to make other blocks
	// Make new block
	MemoryBlock* new_mblock = (MemoryBlock*)((char*)_data(mblock) + size);
	s_size(new_mblock, _size(mblock) - size - sizeof(MemoryBlock));
	s_free(new_mblock, true);

	if (_next(mblock))
		s_prev(_next(mblock), new_mblock);

	// Return the old block
	s_size(mblock, size);
	s_prev(new_mblock, mblock);

	return _data(mblock);
};

// Free memory previously allocated by memalloc
void memfree(void* p) {
	if (p < _data(_memory_pool) || p >((char*)_data(_memory_pool) + _pool_size))
		return;

	MemoryBlock* mblock = (MemoryBlock*)((char*)p - sizeof(MemoryBlock));

	s_free(mblock, true);

	// Check if next or previous memory block is also free


	if (_next(mblock)) {
		if (_free(_next(mblock))) {
			s_size(mblock, _size(mblock) + _size(_next(mblock)) + sizeof(MemoryBlock));

			if (_next(mblock))
				s_prev(_next(mblock), mblock);
		}
	}

	if (_prev(mblock)) {
		if (_free(_prev(mblock))) {
			s_size(_prev(mblock), _size(_prev(mblock)) + _size(mblock) + sizeof(MemoryBlock));

			if (_next(mblock))
				s_prev(_next(mblock), _prev(mblock));
		}
	}
};