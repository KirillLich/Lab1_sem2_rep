#define _CRTDBG_MAP_ALLOC
#include "Polynomial.h"


variable* make_var(
	void* coefficient,
	size_t coefficient_size,
	size_t var_degree,
	variable* next_smaller_var
)
{
	variable* result = malloc(sizeof(variable));
	result->coefficient = malloc(coefficient_size);
	memcpy(result->coefficient, coefficient, coefficient_size);
	result->var_degree = var_degree;
	result->next_smaller_var = next_smaller_var;
	return result;
}

void print_var(variable* var, void(*print)(void*))
{
	printf("(");
	print(var->coefficient);
	printf(")");
	if (var->var_degree != 0) {
		printf("X");
		if (var->var_degree != 1) printf("^%d", (int)var->var_degree);
	}
}

void var_del(variable* v, ring* r)
{
	if (v == NULL)return;
	if (v->next_smaller_var != NULL) var_del(v->next_smaller_var, r);
	r->delete(v->coefficient);
	free(v);
	//free(v->coefficient);
}

variable* node_sum(variable* first_node, variable* second_node, ring* ring_info)
{
	void* coef_res = ring_info->sum(first_node->coefficient, second_node->coefficient);
	if (ring_info->compare(coef_res, ring_info->zero) == 0)
	{
		ring_info->delete(coef_res);
		//free(coef_res);
		return NULL;
	}
	else
	{
		variable* res = malloc(sizeof(variable));
		res->coefficient = coef_res;
		res->next_smaller_var = NULL;
		res->var_degree = first_node->var_degree;
		return res;
	}
}

variable* var_cpy(variable* v, size_t size_of_coef)
{
	if (v == NULL)return NULL;
	variable* res = malloc(sizeof(variable));
	res->coefficient = malloc(size_of_coef);
	res->next_smaller_var = NULL;
	res->var_degree = v->var_degree;
	memcpy(res->coefficient, v->coefficient, size_of_coef);
	return res;
}

variable* var_cpy_all(variable* v, size_t size_of_coef)
{
	variable* res, *ptr_res, *ptr_v;
	res = var_cpy(v, size_of_coef);
	ptr_res = res;
	ptr_v = v->next_smaller_var;
	while (ptr_v != NULL)
	{
		ptr_res->next_smaller_var = var_cpy(ptr_v, size_of_coef);
		ptr_res = ptr_res->next_smaller_var;
		ptr_v = ptr_v->next_smaller_var;
	}
	return res;
}

variable* var_sum(variable* first, variable* second, ring* ring_info)
{
	variable* result=NULL, *p, * first_ptr = first, * second_ptr = second;
	size_t size_of_coef = ring_info->size;
	while (result == NULL)
	{
		if (first_ptr == NULL && second_ptr == NULL)return NULL;
		else if(first_ptr==NULL) 
		{
			result = var_cpy(second_ptr, size_of_coef);
			second_ptr = second_ptr->next_smaller_var;
		}
		else if (second_ptr == NULL)
		{
			result = var_cpy(first_ptr, size_of_coef);
			first_ptr = first_ptr->next_smaller_var;
		}
		if (result != NULL)break;

		if (first_ptr->var_degree > second_ptr->var_degree)
		{
			result = var_cpy(first_ptr, size_of_coef);
			first_ptr = first_ptr->next_smaller_var;
		}
		else if (first_ptr->var_degree < second_ptr->var_degree)
		{
			result = var_cpy(second_ptr, size_of_coef);
			second_ptr = second_ptr->next_smaller_var;
		}
		else if (first_ptr->var_degree == second_ptr->var_degree)
		{
			result = node_sum(first_ptr, second_ptr, ring_info);
			first_ptr = first_ptr->next_smaller_var;
			second_ptr = second_ptr->next_smaller_var;
		}
	}
	p = result;
	while (first_ptr != NULL || second_ptr != NULL)
	{
		if (first_ptr == NULL)
		{
			while (second_ptr != NULL)
			{
				p->next_smaller_var = var_cpy(second_ptr, size_of_coef);
				p = p->next_smaller_var;
				second_ptr = second_ptr->next_smaller_var;
			}
		}
		else if (second_ptr == NULL)
		{
			while (first_ptr != NULL)
			{
				p->next_smaller_var = var_cpy(first_ptr, size_of_coef);
				p = p->next_smaller_var;
				first_ptr = first_ptr->next_smaller_var;
			}
		}
		else
		{
			if (first_ptr->var_degree > second_ptr->var_degree)
			{
				p->next_smaller_var = var_cpy(first_ptr, size_of_coef);
				p = p->next_smaller_var;
				first_ptr = first_ptr->next_smaller_var;
			}
			else if (first_ptr->var_degree < second_ptr->var_degree)
			{
				p->next_smaller_var = var_cpy(second_ptr, size_of_coef);
				p = p->next_smaller_var;
				second_ptr = second_ptr->next_smaller_var;
			}
			else if (first_ptr->var_degree == second_ptr->var_degree)
			{
				p->next_smaller_var = node_sum(first_ptr, second_ptr, ring_info);
				first_ptr = first_ptr->next_smaller_var;
				second_ptr = second_ptr->next_smaller_var;
				if(p->next_smaller_var!=NULL) p = p->next_smaller_var;
			}
		}
	}
	return result;
}

variable* var_mult_scalar(variable* var, void* scalar, ring* ring_info)
{
	if (ring_info->compare(scalar, ring_info->zero) == 0) return NULL;
	variable* ptr = var;

	void* coef = ring_info->mult(scalar, var->coefficient);
	variable* res = make_var(coef, ring_info->size, var->var_degree, NULL);
	ring_info->delete(coef);
	ptr = var->next_smaller_var;

	variable* ptr_res = res;
	while (ptr != NULL)
	{
		coef = ring_info->mult(scalar, ptr->coefficient);
		ptr_res->next_smaller_var = make_var(coef, ring_info->size, ptr->var_degree, NULL);
		ring_info->delete(coef);
		ptr_res = ptr_res->next_smaller_var;
		ptr = ptr->next_smaller_var;
	}
	return res;
}

variable* var_degree_increase(variable* var, size_t coef_size, size_t in)
{
	if (var == NULL)return NULL;
	variable* res = make_var(var->coefficient, coef_size, var->var_degree + in, var_degree_increase(var->next_smaller_var, coef_size, in));
	return res;
}

variable* var_mult_var(variable* first, variable* second, ring* ring_info)
{
	variable* res = NULL;
	variable* ptr = second, *after_mult, *after_increase, *help_ptr;
	int diff;
	while (ptr != NULL)
	{
		after_mult = var_mult_scalar(first, ptr->coefficient, ring_info);

		diff = ptr->var_degree;
		if (ptr->next_smaller_var != NULL)diff -= (ptr->next_smaller_var->var_degree);

		after_increase = var_degree_increase(after_mult, ring_info->size, ptr->var_degree);
		var_del(after_mult, ring_info);
		help_ptr = var_sum(res, after_increase, ring_info);
		var_del(after_increase, ring_info);
		var_del(res, ring_info);
		res = help_ptr;
		help_ptr = NULL;

		ptr = ptr->next_smaller_var;
	}
	
	return res;
}

void* var_calculate(variable* var, void* x, ring* ring_info)
{
	variable* ptr = var;
	void* res = NULL, * b;
	int t;

	while (ptr != NULL)
	{
		if (res != NULL)
		{
			b = ring_info->sum(res, ptr->coefficient);
			ring_info->delete(res);
		}
		else
		{
			b = ring_info->make();
			memcpy(b, ptr->coefficient, ring_info->size);
		}
		res = b;
		if (ptr->next_smaller_var != NULL)t = ptr->next_smaller_var->var_degree;
		else t = 0;
		for (size_t i = 0; i < ptr->var_degree-t; i++)
		{
			b = ring_info->mult(res, x);
			ring_info->delete(res);
			res = b;
		}
		ptr = ptr->next_smaller_var;
	}
	return res;
}

variable* var_in_degree(variable* var, size_t degree, ring* ring_info)
{
	variable* res;
	variable* ptr;
	if (degree == 0)
	{
		res = make_var(ring_info->unit, ring_info->size, 0, NULL);
	}
	else
	{
		res = var_cpy_all(var, ring_info->size);
		for (int i = 1; i < degree; i++)
		{
			ptr = var_mult_var(res, var, ring_info);
			var_del(res, ring_info);
			res = ptr;
		}
	}
	return res;
}

variable* var_composition(variable* first, variable* second, ring* ring_info)
{
	variable* ptr = first, *help_ptr_1 = second, *res = NULL, * help_ptr_2;
	while (ptr != NULL)
	{
		help_ptr_1 = var_in_degree(second,ptr->var_degree,ring_info);
		help_ptr_2 = var_mult_scalar(help_ptr_1, ptr->coefficient, ring_info);
		var_del(help_ptr_1, ring_info);
		if (res == NULL)
		{
			res = help_ptr_2;
		}
		else
		{
			help_ptr_1 = var_sum(res, help_ptr_2, ring_info);
			var_del(res, ring_info);
			var_del(help_ptr_2, ring_info);
			res = help_ptr_1;
		}
		ptr = ptr->next_smaller_var;
	}
	return res;
}

int node_compair(variable* first, variable* second, ring* ring_info)
{
	if (first == NULL)
	{
		if (second == NULL) return 1;
		else return 0;
	}
	else
	{
		if (second == NULL) return 0;
		if (
			first->var_degree == second->var_degree &&
			ring_info->compare(first->coefficient, second->coefficient) == 0
			)
			return 1;
		else return 0;
	}
}

int var_compair(variable* first, variable* second, ring* ring_info)
{
	variable* ptr1 = first, * ptr2 = second;
	int k;
	while (ptr1 != NULL || ptr2 != NULL)
	{
		k = node_compair(ptr1, ptr2, ring_info);
		if (k == 0)
		{
			ptr1 = NULL;
			ptr2 = NULL;
			return 0;
		}
		else
		{
			ptr1 = ptr1->next_smaller_var;
			ptr2 = ptr2->next_smaller_var;
		}
	}
	return 1;
}

polynomial* make_polynom(ring* ring_info, variable* coeff_from_high_degree_to_low)
{
	if(ring_info==NULL)
	{
		fprintf(stderr, "invalid ring pointer");
		return NULL;
	}
	polynomial* result = malloc(sizeof(polynomial));
	result->ring_info = ring_info;
	result->degree = coeff_from_high_degree_to_low->var_degree;
	result->maximum_degree_var = coeff_from_high_degree_to_low;
	return result;
}

void del_polynom(polynomial** p)
{
	if (*p == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return;
	}
	var_del((*p)->maximum_degree_var, (*p)->ring_info);
	free(( * p));
	*p = NULL;
}

void print_polynom(polynomial* p)
{
	if (p == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return;
	}
	variable* ptr = p->maximum_degree_var;
	while (ptr != NULL)
	{
		print_var(ptr, p->ring_info->print);
		ptr = ptr->next_smaller_var;
		if (ptr != NULL)printf("+");
	}
}

polynomial* polynom_sum(polynomial* first, polynomial* second)
{
	if (first == NULL || second == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return NULL;
	}
	variable* sum = var_sum(first->maximum_degree_var, second->maximum_degree_var, first->ring_info);
	polynomial* pol = make_polynom(first->ring_info, sum);
	return pol;
}

polynomial* polynom_mult_sc(polynomial* first, void* second)
{
	if (first == NULL || second == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return NULL;
	}
	variable* mult = var_mult_scalar(first->maximum_degree_var, second, first->ring_info);
	polynomial* pol = make_polynom(first->ring_info, mult);
	return pol;
}

polynomial* polynom_mult_polynom(polynomial* first, polynomial* second)
{
	if (first == NULL || second == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return NULL;
	}
	variable* mult = var_mult_var(first->maximum_degree_var, second->maximum_degree_var, first->ring_info);
	polynomial* pol = make_polynom(first->ring_info, mult);
	return pol;
}

void* polynom_calculate(polynomial* p, void* x)
{
	if (p == NULL || x == NULL) {
		if (p == NULL) fprintf(stderr, "invalid polynom pointer");
		else fprintf(stderr, "invalid value");
		return NULL;
	}
	void* calc = var_calculate(p->maximum_degree_var, x, p->ring_info);
	//polynomial* pol = make_polynom(p->ring_info, calc);
	return calc;
}

polynomial* polynom_composition(polynomial* first, polynomial* second)
{
	if (first == NULL || second == NULL)
	{
		fprintf(stderr, "invalid polynom pointer");
		return NULL;
	}
	variable* comp = var_composition(first->maximum_degree_var, second->maximum_degree_var, first->ring_info);
	polynomial* res = make_polynom(first->ring_info, comp);
	return res;
}

polynomial* polynom_interface(void* (*scan_func)(), ring* ring_info, size_t degree, int* error)
{

	if (scan_func == NULL)
	{
		fprintf(stderr, "invalid scan function pointer");
		*error = -4;
		return NULL;
	}
	if (ring_info == NULL)
	{
		fprintf(stderr, "invalid ring pointer");
		*error = -5;
		return NULL;
	}
	char* field_name;
	int err = check_correct_ring(ring_info, &field_name);
	if (err != 0)
	{
		fprintf(stderr, "error: %d, ivalid field %s", err, field_name);
		*error = err;
		return NULL;
	}

	void* a;
	variable* res = malloc(sizeof(variable));
	variable* ptr = res;
	a = scan_func();
	res->coefficient = a;
	res->var_degree = degree;
	for (int i = 1; i <= degree; i++)
	{
		a = scan_func();
		if (ring_info->compare(ring_info->zero, a) == 0)continue;
		ptr->next_smaller_var = malloc(sizeof(variable));
		ptr = ptr->next_smaller_var;
		ptr->coefficient = a;
		ptr->var_degree = degree - i;
	}
	ptr->next_smaller_var = NULL;

	polynomial* pol = make_polynom(ring_info, res);
	return pol;
}

int polynom_compair(polynomial* first, polynomial* second)
{
	if (first->degree != second->degree)return 0;
	else
	{
		return var_compair(first->maximum_degree_var, second->maximum_degree_var, first->ring_info);
	}
}