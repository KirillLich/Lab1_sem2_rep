#include "variable_int.h"

void* sum_int(void* a, void* b)
{
	void* result = malloc(sizeof(int));
	*((int*)result) = *((int*)a) + *((int*)b);
	return result;
}

void* mult_int(void* a, void* b)
{
	void* result = malloc(sizeof(int));
	*((int*)result) = *((int*)a) * *((int*)b);
	return result;
}

void print_int(void* a)
{
	printf("%d", *((int*)a));
}

int compare_int(void* a, void* b)
{
	if (*((int*)a) > *((int*)b))return 1;
	else if (*((int*)a) < *((int*)b))return-1;
	else return 0;
}

void delete_int(void* a)
{
	free((int*)a);
}

void* make_int()
{
	return malloc(sizeof(int));
}