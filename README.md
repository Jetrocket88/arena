Usage:

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"
 
int main() {
    Arena* arena;
    arena_create(arena, 10000);
    char *a = arena_push(arena, 1000);
    char *b = arena_push(arena, 100);
    char *c = arena_push(arena, 200);
    arena_space_used(arena);


}
