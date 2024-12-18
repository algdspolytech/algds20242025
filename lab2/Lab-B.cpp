#include "memallocator.h"

typedef struct BlockHeader {
    int size;
    int is_free;
    struct BlockHeader* next;
    struct BlockHeader* prev;
} BlockHeader;

static void* memory_start = NULL;
static BlockHeader* first_block = NULL;

int meminit(void* pMemory, int size) {
    if (!pMemory || size < (int)sizeof(BlockHeader))
        return 0;

    memory_start = pMemory;
    first_block = (BlockHeader*)pMemory;

    first_block->size = size - (int)sizeof(BlockHeader);
    first_block->is_free = 1;
    first_block->next = NULL;
    first_block->prev = NULL;

    return 1;
}

void memdone() {
    memory_start = NULL;
    first_block = NULL;
}

void* memalloc(int size) {
    if (size <= 0 || !first_block)
        return NULL;

    BlockHeader* best_block = NULL;
    BlockHeader* current = first_block;
    int best_size_diff = -1;

    while (current) {
        if (current->is_free && current->size >= size) {
            int size_diff = current->size - size;
            if (best_size_diff == -1 || size_diff < best_size_diff) {
                best_size_diff = size_diff;
                best_block = current;
            }
        }
        current = current->next;
    }

    if (!best_block)
        return NULL;

    if (best_size_diff >= (int)(sizeof(BlockHeader) + 1)) {
        BlockHeader* new_block = (BlockHeader*)((char*)best_block + sizeof(BlockHeader) + size);
        new_block->size = best_block->size - size - (int)sizeof(BlockHeader);
        new_block->is_free = 1;
        new_block->next = best_block->next;
        new_block->prev = best_block;

        if (best_block->next)
            best_block->next->prev = new_block;

        best_block->next = new_block;
        best_block->size = size;
    }

    best_block->is_free = 0;
    return (char*)best_block + sizeof(BlockHeader);
}

void memfree(void* p) {
    if (!p)
        return;

    BlockHeader* block = (BlockHeader*)((char*)p - sizeof(BlockHeader));
    block->is_free = 1;

    if (block->next && block->next->is_free) {
        block->size += sizeof(BlockHeader) + block->next->size;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }

    if (block->prev && block->prev->is_free) {
        block->prev->size += sizeof(BlockHeader) + block->size;
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
    }
}

int memgetminimumsize() {
    return (int)sizeof(BlockHeader);
}

int memgetblocksize() {
    return (int)sizeof(BlockHeader);
}
