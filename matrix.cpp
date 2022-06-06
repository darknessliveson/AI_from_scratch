#include "matrix.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define MAXCHAR 100

Matrix::Matrix(int row, int col) {
	rows = row;
	cols = col;
	entries = new double*;
	for (int i = 0; i < rows; i++) {
		entries[i] = new double[cols];
		for (int j = 0; j < cols; j++) {
			entries[i][j] = 0;
		}
	}
}

void Matrix::matrix_fill(int n) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			entries[i][j] = n;
		}
	}
}

Matrix::~Matrix() {
}

void Matrix::matrix_print() {
	printf("Rows:%d Columns: %d\n", rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%1.3f ", entries[i][j]);
		}
		printf("\n");
	}
}

Matrix* Matrix::matrix_copy(Matrix* m) {
	Matrix* mat = new Matrix(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat->entries[i][j] = entries[i][j];
		}
	}
	return mat;
}

void Matrix::matrix_save(char* file_string) {
	std::ofstream file;
	file.open(file_string, std::ios::out);
	file << rows;
	file << cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			file << entries[i][j];
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

	Matrix* m = new Matrix(rows, cols);
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

void Matrix::matrix_randomize(int n) {
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			entries[i][j] = uniform_distribution(min, max);
		}
	}
}

int Matrix::matrix_argmax() {
	double max_score = 0;
	int max_idx = 0;
	for (int i = 0; i < rows; i++) {
		if (entries[i][0] > max_score) {
			max_score = entries[i][0];
			max_idx = i;
		}
	}
	return max_idx;
}

Matrix* Matrix::matrix_flatten(int axis) {
	Matrix* mat;
	if (axis == 0) {
		mat = new Matrix(rows * cols, 1);
	}
	else if (axis == 1) {
		mat = new Matrix(1, rows * cols);
	}
	else {
		printf("Argument to matrix_flatten must be 0 or 1");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (axis == 0)
				mat->entries[i * cols + j][0] = entries[i][j];
			else if (axis == 1) {
				mat->entries[0][i * cols + j] = entries[i][j];
			}
		}
	}
	return mat;
}
