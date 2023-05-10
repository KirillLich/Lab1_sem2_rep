#ifndef RING_H
#define RING_H
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ring
{
	size_t size;
	void* zero;//нулевой
	void* unit;
	void* (*sum)(void*, void*);//сумма
	void* (*mult)(void*, void*);//перемножение
	void (*print)(void*);
	int (*compare)(void*, void*);
	void (*delete)(void*);
	void* (*make)();
} ring;

ring* create_ring(
	size_t size,
	void* zero,
	void* unit,
	void* (*sum)(void*, void*),
	void* (*mult)(void*, void*),
	void (*print)(void*),
	int (*compare)(void*, void*),
	void (*delete)(void*),
	void*(*make)()
);

int check_correct_ring(ring* r, char* field_name);

void del_ring(ring** r);

ring* ringcpy(ring* r, ring* p);
#endif // !RING_H