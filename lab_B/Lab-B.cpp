#include "memallocator.h"

// Структура для хранения информации о блоке памяти
typedef struct BlockHeader {
    int size;                  // Размер блока данных (без учета заголовка)
    int is_free;              // Флаг, указывающий, свободен ли блок
    struct BlockHeader* next;  // Указатель на следующий блок
    struct BlockHeader* prev;  // Указатель на предыдущий блок
} BlockHeader;

// Глобальные указатели на начало памяти и первый блок
static void* memory_start = 0;
static BlockHeader* first_block = 0;

// Инициализация системы управления памятью
int meminit(void* pMemory, int size) {
    if (!pMemory || size < sizeof(BlockHeader))
        return 0;

    memory_start = pMemory;
    first_block = (BlockHeader*)pMemory;
    
    // Инициализация первого блока
    first_block->size = size - sizeof(BlockHeader);
    first_block->is_free = 1;
    first_block->next = 0;
    first_block->prev = 0;
    
    return 1;
}

void memdone() {
    // Очистка указателей
    memory_start = 0;
    first_block = 0;
}

void* memalloc(int size) {
    if (size <= 0 || !first_block)
        return 0;

    BlockHeader* best_block = 0;
    BlockHeader* current = first_block;
    int best_size_diff = -1;

    // Поиск блока с наименьшей разницей в размере (лучший подходящий)
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
        return 0;

    // Если оставшегося места достаточно для нового блока
    if (best_size_diff >= sizeof(BlockHeader) + 1) {
        BlockHeader* new_block = (BlockHeader*)((char*)best_block + sizeof(BlockHeader) + size);
        new_block->size = best_block->size - size - sizeof(BlockHeader);
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

    // Слияние с следующим свободным блоком
    if (block->next && block->next->is_free) {
        block->size += sizeof(BlockHeader) + block->next->size;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }

    // Слияние с предыдущим свободным блоком
    if (block->prev && block->prev->is_free) {
        block->prev->size += sizeof(BlockHeader) + block->size;
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
    }
}

int memgetminimumsize() {
    return sizeof(BlockHeader);
}

int memgetblocksize() {
    return sizeof(BlockHeader);
}
