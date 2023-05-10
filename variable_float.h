#ifndef VARIABLEFLOAT_H
#define VARIABLEFLOAT_H
#include <stdio.h>
#include <stdlib.h>

void* sum_float(void* a, void* b);

void* mult_float(void* a, void* b);

void print_float(void* a);

int compare_float(void* a, void* b);

void delete_float(void* a);

void* make_float();
#endif // !