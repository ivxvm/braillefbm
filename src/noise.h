// value noise with cosine interpolation

#pragma once

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

struct Noise {
    int values_count;
    float* values;
};

void noise_init(struct Noise* noise, int values_count) {
    noise->values_count = values_count;
    noise->values = malloc(values_count * sizeof(float));
    for (int i = 0; i < values_count; i++) {
        float n = rand() % 1000;
        noise->values[i] = n / 1000.0;
    }
}

float noise_lookup(struct Noise* noise, float x) {
    double _;
    x = modf(x, &_);
    int n = noise->values_count;
    float pivot = x * n;
    int a = (int) pivot;
    int b = a == n - 1 ? 0 : a + 1;
    float ya = noise->values[a];
    float yb = noise->values[b];
    float t = pivot - (float)a;
    float ts = (1 - cos(t * M_PI)) * 0.5;
    return ya + (yb - ya) * ts;
}

void noise_free(struct Noise* noise) {
    free(noise->values);
}
