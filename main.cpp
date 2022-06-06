#include <stdio.h>
#include <iostream>
#include "matrix.h"

int main() {
	printf("Hello Darkness");
	Matrix* m = new Matrix(3,3);
	m->matrix_fill(3);
	m->matrix_print();
	Matrix* mat = m->matrix_copy(m);	
	mat->matrix_fill(5);
	mat->matrix_print();
	std::cin.get();
	return 0;
}
