#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include "Polynomial.h"
#include "Ring.h"
#include "variable_int.h"
#include "variable_float.h"
#include <stdio.h>
#include <stdlib.h>

int* scanf_int()
{
	int* a = malloc(sizeof(int));
	scanf("%d", a);
	scanf("%*c");
	return a;
}

float* scanf_float()
{
	float* a = malloc(sizeof(float));
	scanf("%f", a);
	scanf("%*c");
	return a;
}

void testing_visual_int()
{
	//#1 - making int ring
	int* ZERO = malloc(sizeof(int));
	*ZERO = 0;
	int* UNIT = malloc(sizeof(int));
	*UNIT = 1;
	ring* ring_int = create_ring(
		sizeof(int),
		ZERO,
		UNIT,
		sum_int,
		mult_int,
		print_int,
		compare_int,
		delete_int,
		make_int
	);

	//#2 - making and printing polynomial
	int DEGREE = 5;
	int* err = malloc(sizeof(int));
	polynomial* pol1 = polynom_interface(scanf_int, ring_int, DEGREE, err);
	printf("polynom1 = ");
	print_polynom(pol1);
	printf("\n");

	//#3 - summation of 2 equal polynoms
	polynomial* pol2 = polynom_sum(pol1, pol1);
	printf("polynom1 + polynom1= ");
	print_polynom(pol2);
	printf("\n");

	//#4 summation of 2 non equal polynoms
	DEGREE = 3;
	polynomial* pol3 = polynom_interface(scanf_int, ring_int, DEGREE, err);
	printf("polynom2 = ");
	print_polynom(pol3);
	printf("\n");

	polynomial* pol4 = polynom_sum(pol1, pol3);
	printf("polynom1 + polynom2= ");
	print_polynom(pol4);
	printf("\n");

	//#5 multiplication to scalar
	int* sc = malloc(sizeof(int));
	*sc = 5;
	polynomial* pol5 = polynom_mult_sc(pol4, sc);
	printf("5*(polynom1 + polynom2)= ");
	print_polynom(pol5);
	printf("\n");

	//#6 mult two polynoms
	polynomial* polynom_mult = polynom_mult_polynom(pol1, pol3);
	printf("polynom1 * polynom2= ");
	print_polynom(polynom_mult);
	printf("\n");

	//#7 calculation with x
	int* x = malloc(sizeof(int));
	*x = 5;
	int* res = polynom_calculate(pol2, x);
	if (res != NULL)
	{
		printf("(polynom1 + polynom1)(5)= ");
		print_int(res);
	}
	printf("\n");

	//#8 composition
	polynomial* pol6 = polynom_composition(pol1, pol3);
	printf("polynom1(polynom2)=");
	print_polynom(pol6);

	//#9 deleting polynoms and over pointers
	del_polynom(&pol1);
	del_polynom(&pol2);
	del_polynom(&pol3);
	del_polynom(&pol4);
	del_polynom(&pol5);
	del_polynom(&pol6);
	del_polynom(&polynom_mult);
	del_ring(&ring_int);

	free(sc);
	free(x);
	free(res);
	free(ZERO);
	free(UNIT);
	free(err);
}

void testing_visual_float()
{
	//#1 - making int ring
	float* ZERO = malloc(sizeof(float));
	*ZERO = 0.0;
	float* UNIT = malloc(sizeof(float));
	*UNIT = 1.0;
	ring* ring_float = create_ring(
		sizeof(float),
		ZERO,
		UNIT,
		sum_float,
		mult_float,
		print_float,
		compare_float,
		delete_float,
		make_float
	);

	//#2 - making and printing polynomial
	int DEGREE = 5;
	int* err = malloc(sizeof(int));
	polynomial* pol1 = polynom_interface(scanf_float, ring_float, DEGREE, err);
	printf("polynom1 = ");
	print_polynom(pol1);
	printf("\n");

	//#3 - summation of 2 equal polynoms
	polynomial* pol2 = polynom_sum(pol1, pol1);
	printf("polynom1 + polynom1= ");
	print_polynom(pol2);
	printf("\n");

	//#4 summation of 2 non equal polynoms
	DEGREE = 3;
	polynomial* pol3 = polynom_interface(scanf_float, ring_float, DEGREE, err);
	printf("polynom2 = ");
	print_polynom(pol3);
	printf("\n");

	polynomial* pol4 = polynom_sum(pol1, pol3);
	printf("polynom1 + polynom2= ");
	print_polynom(pol4);
	printf("\n");

	//#5 multiplication to scalar
	float* sc = malloc(sizeof(int));
	*sc = 0.1;
	polynomial* pol5 = polynom_mult_sc(pol4, sc);
	printf("0.1*(polynom1 + polynom2)= ");
	print_polynom(pol5);
	printf("\n");

	//#6 mult two polynoms
	polynomial* polynom_mult = polynom_mult_polynom(pol1, pol3);
	printf("polynom1 * polynom2= ");
	print_polynom(polynom_mult);
	printf("\n");

	//#7 calculation with x
	float* x = malloc(sizeof(int));
	*x = 5.0;
	float* res = polynom_calculate(pol2, x);
	if (res != NULL)
		if (res != NULL)
		{
			printf("(polynom1 + polynom1)(5.0)= ");
			print_float(res);
		}
	printf("\n");

	//#8 composition easy
	polynomial* pol6 = polynom_composition(pol1, pol3);
	printf("polynom1(polynom2)=");
	print_polynom(pol6);

	//#9 deleting polynoms and over pointers
	del_polynom(&pol1);
	del_polynom(&pol2);
	del_polynom(&pol3);
	del_polynom(&pol4);
	del_polynom(&pol5);
	del_polynom(&pol6);
	del_polynom(&polynom_mult);
	del_ring(&ring_float);

	free(sc);
	free(x);
	free(res);
	free(ZERO);
	free(UNIT);
	free(err);
}

void initial_testing_variables(
	variable** var1,
	variable** var2,
	variable** sum,
	variable** mult_sc,
	variable** mult,
	void** calc,
	variable** comp)
{
	//var1 = x^2+2x+3
	int* a = malloc(sizeof(int)), * b = malloc(sizeof(int)), * c = malloc(sizeof(int));
	*a = 1;
	*b = 2;
	*c = 3;
	*var1 = make_var(a, sizeof(int), 2,
		make_var(b, sizeof(int), 1,
			make_var(c, sizeof(int), 0, NULL)));

	//var2 = x^4-x^3+2x^2-8
	int* d = malloc(sizeof(int));
	*a = 1;
	*b = -1;
	*c = 2;
	*d = -8;
	*var2 = make_var(a, sizeof(int), 4,
		make_var(b, sizeof(int), 3,
			make_var(c, sizeof(int), 2,
				make_var(d, sizeof(int), 0, NULL))));

	//sum = x^4-x^3+3x^2+2x-5
	int* e = malloc(sizeof(int));
	*a = 1;
	*b = -1;
	*c = 3;
	*d = 2;
	*e = -5;
	*sum = make_var(a, sizeof(int), 4,
		make_var(b, sizeof(int), 3,
			make_var(c, sizeof(int), 2,
				make_var(d, sizeof(int), 1, 
					make_var(e, sizeof(int), 0, NULL)))));

	//mult_sc = var2 * 3 = 3x^4-3x^3+6x^2-24
	*a = 3;
	*b = -3;
	*c = 6;
	*d = -24;
	*mult_sc = make_var(a, sizeof(int), 4,
		make_var(b, sizeof(int), 3,
			make_var(c, sizeof(int), 2,
				make_var(d, sizeof(int), 0, NULL))));

	//mult = var1*var2 = x^6+x^5+3x^4+x^3-2x^2-16x-24
	int* f = malloc(sizeof(int)), * g = malloc(sizeof(int));
	*a = 1;
	*b = 1;
	*c = 3;
	*d = 1;
	*e = -2;
	*f = -16;
	*g = -24;
	*mult = make_var(a, sizeof(int), 6,
		make_var(b, sizeof(int), 5,
			make_var(c, sizeof(int), 4,
				make_var(d, sizeof(int), 3, 
					make_var(e, sizeof(int), 2,
						make_var(f, sizeof(int), 1,
							make_var(g, sizeof(int), 0, NULL)))))));

	//calc = mult(-2) = 72
	*calc = malloc(sizeof(int));
	**((int**)calc) = 72;

	//comp = var2(var1) = x^8+8x^7+35x^6+98x^5+195x^4+276x^3+281x^2+186x+64
	int* h = malloc(sizeof(int)), * i = malloc(sizeof(int));
	*a = 1;
	*b = 8;
	*c = 35;
	*d = 98;
	*e = 195;
	*f = 276;
	*g = 281;
	*h = 186;
	*i = 64;
	*comp = make_var(a, sizeof(int), 8,
		make_var(b, sizeof(int), 7,
			make_var(c, sizeof(int), 6,
				make_var(d, sizeof(int), 5,
					make_var(e, sizeof(int), 4,
						make_var(f, sizeof(int), 3,
							make_var(g, sizeof(int), 2, 
								make_var(h, sizeof(int), 1,
									make_var(i, sizeof(int), 0, NULL)))))))));
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	free(g);
	free(h);
	free(i);
}

void testing_right()
{
	int* ZERO = malloc(sizeof(int));
	*ZERO = 0;
	int* UNIT = malloc(sizeof(int));
	*UNIT = 1;
	ring* ring_int = create_ring(
		sizeof(int),
		ZERO,
		UNIT,
		sum_int,
		mult_int,
		print_int,
		compare_int,
		delete_int,
		make_int
	);

	variable* var1 = NULL, * var2 = NULL, * sum = NULL, * var_mult_sc = NULL, * var_mult = NULL, * var_comp = NULL;
	void* calcT = NULL;
	initial_testing_variables(
		&var1,
		&var2,
		&sum,
		&var_mult_sc,
		&var_mult,
		&calcT,
		&var_comp
	);

	polynomial* pol1, * pol2, * pol_sum, * pol_sumT, * pol_mult_sc, * pol_mult_scT, * pol_mult, * pol_multT, * pol_comp, * pol_compT;
	pol1 = make_polynom(ring_int, var1);
	pol2 = make_polynom(ring_int, var2);

	pol_sumT = make_polynom(ring_int, sum);
	pol_mult_scT = make_polynom(ring_int, var_mult_sc);
	pol_multT = make_polynom(ring_int, var_mult);
	pol_compT = make_polynom(ring_int, var_comp);

	pol_sum = polynom_sum(pol1,pol2);
	int* sc = malloc(sizeof(int));
	*sc = 3;
	pol_mult_sc = polynom_mult_sc(pol2,sc);
	pol_mult = polynom_mult_polynom(pol1,pol2);
	pol_comp = polynom_composition(pol2,pol1);
	int* x = malloc(sizeof(int));
	*x = -2;
	void* calc = polynom_calculate(pol_mult, x);

	if (polynom_compair(pol_sumT, pol_sum) == 0)fprintf(stderr ,"err at sum\n");
	if (polynom_compair(pol_mult_scT, pol_mult_sc) == 0)fprintf(stderr, "err at mult_sc\n");
	if (polynom_compair(pol_multT, pol_mult) == 0)fprintf(stderr, "err at mult\n");
	if (polynom_compair(pol_compT, pol_comp) == 0)fprintf(stderr, "err at composition\n");
	if (ring_int->compare(calc,calcT) != 0)fprintf(stderr, "err at calculation\n");
	del_polynom(&pol1);
	del_polynom(&pol2);
	del_polynom(&pol_sum);
	del_polynom(&pol_sumT);
	del_polynom(&pol_mult_sc);
	del_polynom(&pol_mult_scT);
	del_polynom(&pol_mult);
	del_polynom(&pol_multT);
	del_polynom(&pol_comp);
	del_polynom(&pol_compT);
	del_ring(&ring_int);

	free(sc);
	free(x);
	free(calc);
	free(calcT);
	free(ZERO);
	free(UNIT);
}

int main()
{
	//testing_visual_int();
	//testing_visual_float();
	testing_right();
	_CrtDumpMemoryLeaks();
}