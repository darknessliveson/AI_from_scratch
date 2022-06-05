#pragma once
#include <stdlib.h>

double uniform_distribution(double low, double high) {
	double difference = high - low;
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 + (rand() % scaled_difference) / scale);
}