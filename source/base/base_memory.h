/* date = April 6th 2024 9:28 am */

#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

/*
A Memory Arena contains pre-allocated memory, which is accesible
from everywhere in the code. It's a more efficient way of allocating,
freeing and is also a lookup table at the same time.
*/

#include "base_types.h"

struct Arena
{
	U8 *data;
	U64 length;
	U64 offset;
};

// Allocates a new arena
Arena *M_ArenaAlloc(U64 size);

// Pushes new bytes to the end of the arena
void *M_ArenaPush(Arena *arena, U64 size);
// Same function, but it clears out the memory (less efficient)
void *M_ArenaPushZero(Arena *arena, U64 size);

// Pops from the end of the arena the desired size
void *M_ArenaPop(Arena *arena, U64 size);
// Same function, but it clears out the memory (less efficient)
void *M_ArenaPopZero(Arena *arena, U64 size);

// Frees the arenas memory
void M_ArenaFree(Arena *arena);

#endif //BASE_MEMORY_H
