```c
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
```
Very simple and easy to use. Made as a pet project and not for serious use. 
