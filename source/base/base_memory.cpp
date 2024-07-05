#include <malloc.h>
#include <memory.h>
#include "base_inc.h"

Arena *M_ArenaAlloc(U64 size)
{
	U8 *m = (U8*)malloc(size);
	
	Arena *arena = (Arena*)malloc(sizeof(Arena));
	arena->data = m;
	arena->length = size;
	arena->offset = 0;
	
	return arena;
}

void *M_ArenaPush(Arena *arena, U64 size)
{
	if (arena->offset + size > arena->length)
		return NULL;
	
	void *ptr = &arena->data[arena->offset];
	arena->offset += size;
	return ptr;
}

void *M_ArenaPushZero(Arena *arena, U64 size)
{
	void *ptr = M_ArenaPush(arena, size);
	if (ptr != NULL) // Should never happen, but you can't be sure
		memset(ptr, 0, size);
	return ptr;
}

void *M_ArenaPop(Arena *arena, U64 size)
{
	arena->offset -= size;
	return &arena->data[arena->offset];
}

void *M_ArenaPopZero(Arena *arena, U64 size)
{
	void *ptr = M_ArenaPop(arena, size);
	if (ptr != NULL)
		memset(ptr, 0, size);
	return ptr;
}

void M_ArenaFree(Arena *arena)
{
	arena->length = arena->offset = 0;
	free(arena->data);
}