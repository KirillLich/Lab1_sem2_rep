#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#define _CRTDBG_MAP_ALLOC
#include "Ring.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct Variable
{
	void* coefficient;
	size_t var_degree;
	struct Variable* next_smaller_var;
} variable;

variable* make_var(
	void* coefficient,
	size_t coefficient_size,
	size_t var_degree,
	variable* next_smaller_var
);

variable* node_sum(variable* first_node, variable* second_node, ring* ring_info);

void print_var(variable* var, void(*print)(void*));

void var_del(variable* v, ring* r);

variable* var_cpy(variable* v, size_t size_of_coef);

variable* var_cpy_all(variable* v, size_t size_of_coef);

variable* var_sum(variable* first, variable* second, ring* ring_info);

variable* var_degree_increase(variable* var, size_t coef_size, size_t in);

variable* var_mult_scalar(variable* var, void* scalar, ring* ring_info);

variable* var_mult_var(variable* first, variable* second, ring* ring_info);

void* var_calculate(variable* var, void* x, ring* ring_info);

variable* var_in_degree(variable* var, size_t degree, ring* ring_info);

variable* var_composition(variable* first, variable* second, ring* ring_info);

typedef struct Polynomial
{
	size_t degree;
	variable* maximum_degree_var;
	ring* ring_info;
} polynomial;

polynomial* make_polynom(ring* ring_info, variable* coeff_from_high_degree_to_low);

void del_polynom(polynomial** p);

void print_polynom(polynomial* p);

polynomial* polynom_sum(polynomial* first, polynomial* second);

polynomial* polynom_mult_sc(polynomial* first, void* second);

polynomial* polynom_mult_polynom(polynomial* first, polynomial* second);

void* polynom_calculate(polynomial* p, void* x);

polynomial* polynom_composition(polynomial* first, polynomial* second);

polynomial* polynom_interface(void* (*scan_func)(), ring* ring_info, size_t degree, int* error);

int polynom_compair(polynomial* first, polynomial* second);
#endif 