#include "Ring.h"

ring* create_ring(
	size_t size,
	void* zero,
	void* unit,
	void* (*sum)(void*, void*),
	void* (*mult)(void*, void*),
	void (*print)(void*),
	int (*compare)(void*, void*),
	void (*delete)(void*),
	void* (*make)()
)
{
	ring* ring_info = malloc(sizeof(ring));
	ring_info->zero = malloc(sizeof(size));
	memcpy(ring_info->zero, zero, size);
	ring_info->unit = malloc(sizeof(size));
	memcpy(ring_info->unit, unit, size);

	ring_info->size = size;
	ring_info->sum = sum;
	ring_info->mult = mult;
	ring_info->print = print;
	ring_info->compare = compare;
	ring_info->delete = delete;
	ring_info->make = make;

	return ring_info;
}

int check_correct_ring(ring* r, char** field_name)
{
	if (r->compare == NULL)
	{
		*field_name = "compare";
		return 1;
	}
	if (r->delete == NULL)
	{
		*field_name = "delete";
		return 2;
	}
	if (r->make == NULL)
	{
		*field_name = "make";
		return 3;
	}
	if (r->mult == NULL)
	{
		*field_name = "mult";
		return 4;
	}
	if (r->print == NULL)
	{
		*field_name = "mult";
		return 5;
	}
	if (r->size == 0)
	{
		*field_name = "size";
		return -1;
	}
	if (r->sum == NULL)
	{
		*field_name = "sum";
		return 6;
	}
	if (r->unit == NULL)
	{
		*field_name = "unit";
		return -2;
	}
	if (r->zero == NULL)
	{
		*field_name = "zero";
		return -3;
	}
	return 0;
}

void del_ring(ring** r)
{
	(*r)->delete((*r)->zero);
	(*r)->delete((*r)->unit);
	free((*r));
	//*r = NULL;
}

ring* ringcpy(ring* r, ring* p)
{
	memcpy(r, p, sizeof(ring));
	r->zero = malloc(p->size);
	memcpy(r->zero, p->zero, p->size);
	r->unit = malloc(p->size);
	memcpy(r->unit, p->unit, p->size);
	return r;
}