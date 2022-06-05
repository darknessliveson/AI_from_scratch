#include <string>
#pragma once
class Matrix{

private:
	double** entries;
	int rows;
	int cols;

public:
	Matrix* matrix_create(int rows, int columns);
	void matrix_fill(Matrix* m, int n);
	void matrix_free(Matrix* m);
	void matrix_print(Matrix* m);
	Matrix* matrix_copy(Matrix* m);
	void matrix_save(Matrix* m, char* file_string);
	Matrix* matrix_load(char* file_string);
	void matrix_randomize(Matrix* m, int n);
	int matrix_argmax(Matrix* m);
	Matrix* matrix_flatten(Matrix* m, int axis);
};

