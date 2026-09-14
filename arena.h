#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
    void* buffer;
    size_t capacity;
    size_t offset;
} Arena;

#define ARENA_ALIGNMENT _Alignof(max_align_t)

bool arena_create(Arena* arena, size_t capacity);
void arena_clear(Arena *arena);
void arena_destroy(Arena *arena);
void* arena_push(Arena *arena, size_t size);
void arena_rewind(Arena *arena, size_t mark);
void arena_space_used(Arena *arena);

#endif //ARENA_H

#ifdef ARENA_IMPLEMENTATION

bool arena_create(Arena* arena, size_t capacity) {

    arena->buffer = malloc(capacity);
    if (!arena->buffer) { return 0; }

    arena->capacity = capacity;
    arena->offset = 0;

    return 1;
}

void* arena_push(Arena *arena, size_t size) {

    size_t aligned_offset = (arena->offset + ARENA_ALIGNMENT - 1) & ~(ARENA_ALIGNMENT - 1);
    if (aligned_offset > arena->capacity 
        || size > arena->capacity - aligned_offset)
    { 
        printf("Allocating too much!\n");
        return NULL;
    }

    void* ptr = (unsigned char *)arena->buffer + aligned_offset;
    arena->offset = aligned_offset + size;

    return ptr;
}

void arena_clear(Arena *arena) {
    arena->offset = 0;
}

void arena_destroy(Arena *arena) {
    free(arena->buffer);

    arena->offset = 0;
    arena->buffer = NULL;
}

void arena_rewind(Arena *arena, size_t mark) {
    arena->offset = mark;
}

void arena_space_used(Arena *arena) {
    float progress = (float)arena->offset / (float)arena->capacity;
    printf("Arena space used: %.1f%%\n", progress*100);
}

#endif

