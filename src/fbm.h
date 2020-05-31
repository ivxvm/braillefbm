// fractal brownian motion

#pragma once

float fbm(
    int octaves,
    float lacunarity,
    float gain,
    float x,
    float (*noise_cb)(void*, float),
    void* noise_cb_ctx
) {
    float amp = 0.5;
    float freq = 1;
    float y = 0;
    for (int i = 0; i < octaves; i++) {
        y += amp * noise_cb(noise_cb_ctx, freq * x);
        freq *= lacunarity;
        amp *= gain;
    }
    return y;
}
