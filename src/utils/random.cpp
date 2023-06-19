#include "random.h"
#include <random>

float randomf() {
    return (float) rand() / (float) (RAND_MAX);
}

float randomf(float a, float b) {
    return a + randomf() * (b - a);
}