#pragma once
class Matrix{

private:
	int rows;
	int cols;
	double **entries;

public:
	Matrix(int rows, int columns);
	void matrix_fill(int n);
	~Matrix();
	void matrix_print();
	Matrix* matrix_copy(Matrix* m);
	void matrix_save(char* file_string);
	Matrix* matrix_load(char* file_string);
	void matrix_randomize(int n);
	int matrix_argmax();
	Matrix* matrix_flatten(int axis);
};

