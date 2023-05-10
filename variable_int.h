#ifndef VARIABLEINT_H
#define VARIABLEINT_H
#include <stdio.h>
#include <stdlib.h>

void* sum_int(void* a, void* b);

void* mult_int(void* a, void* b);

void print_int(void* a);

int compare_int(void* a, void* b);

void delete_int(void* a);

void* make_int();
#endif // !VARIABLEINT_H