#include "matrix.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define MAXCHAR 100

Matrix* Matrix::matrix_create(int row, int col) {
	Matrix* m = new Matrix;
	m->rows = row;
	m->cols = col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			m->entries[i][j] = 0;
		}
	}
	return m;
}

void Matrix::matrix_fill(Matrix *m, int n) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = n;
		}
	}
}

void Matrix::matrix_free(Matrix* m) {
	delete m;
}

void Matrix::matrix_print(Matrix* m) {
	printf("Rows:%d Columns: %d\n", m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%1.3f ", m->entries[i][j]);
		}
		printf("\n");
	}
}

Matrix* Matrix::matrix_copy(Matrix* m) {
	Matrix* mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] = m->entries[i][j];
		}
	}
	return mat;
}

void Matrix::matrix_save(Matrix* m, char* file_string) {
	std::ofstream file;
	file.open(file_string, std::ios::out);
	file << m->rows;
	file << m->cols;
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			file << m->entries[i][j];
		}
	}
	printf("Successfully saved matrix to %s", file_string);
	file.close();
}

Matrix* Matrix::matrix_load(char* file_string) {
	std::ifstream file;
	file.open(file_string, std::ios::in);
	char entry[MAXCHAR];
	file >> entry;
	int rows = atoi(entry);
	file >> entry;
	int cols = atoi(entry);

	Matrix* m = matrix_create(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			file >> entry;
			m->entries[i][j] = strtod(entry, NULL);
		}
	}
	printf("Successfully loaded matrix from %s", file_string);
	file.close();
	return m;
}

void Matrix::matrix_randomize(Matrix* m, int n) {
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = uniform_distribution(min, max);
		}
	}
}

int Matrix::matrix_argmax(Matrix* m) {
	double max_score = 0;
	int max_idx = 0;
	for (int i = 0; i < m->rows; i++) {
		if (m->entries[i][0] > max_score) {
			max_score = m->entries[i][0];
			max_idx = i;
		}
	}
	return max_idx;
}

Matrix* Matrix::matrix_flatten(Matrix* m, int axis) {
	Matrix* mat;
	if (axis == 0) {
		mat = matrix_create(m->rows * m->cols, 1);
	}
	else if (axis == 1) {
		mat = matrix_create(1, m->rows * m->cols);
	}
	else {
		printf("Argument to matrix_flatten must be 0 or 1");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (axis == 0)
				mat->entries[i * m->cols + j][0] = m->entries[i][j];
			else if (axis == 1) {
				mat->entries[0][i * m->cols + j] = m->entries[i][j];
			}
		}
	}
	return mat;
}
