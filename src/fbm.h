// fractal brownian motion

#pragma once

float fbm(float (*noise)(float), int octaves, float lacunarity, float gain, float x) {
    float amp = 0.5;
    float freq = 1;
    float y = 0;
    for (int i = 0; i < octaves; i++) {
        y += amp * noise(freq * x);
        freq *= lacunarity;
        amp *= gain;
    }
    return y;
}
