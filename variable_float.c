#include "variable_float.h"

void* sum_float(void* a, void* b)
{
	void* result = malloc(sizeof(float));
	*((float*)result) = *((float*)a) + *((float*)b);
	return result;
}

void* mult_float(void* a, void* b)
{
	void* result = malloc(sizeof(float));
	*((float*)result) = *((float*)a) * *((float*)b);
	return result;
}

void print_float(void* a)
{
	printf("%f", *((float*)a));
}

int compare_float(void* a, void* b)
{
	if (*((float*)a) > *((float*)b))return 1;
	else if (*((float*)a) < *((float*)b))return-1;
	else return 0;
}

void delete_float(void* a)
{
	free((float*)a);
}

void* make_float()
{
	return malloc(sizeof(float));
}