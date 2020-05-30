#include <cmath>
#include "math.hh"

float deviation(int x[], int size) {
  float deviation = 0.0, mean, sum = 0;

  for (int i = 0; i < size; i++) {
    sum += x[i];
  }

  mean = sum / size;

  for (int i = 0; i < size; i++) {
    deviation += pow((x[i] - mean), 2);
  }

  return sqrt(deviation / size);
}
