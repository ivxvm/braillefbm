#include <stdlib.h>
#include <stdio.h>
#include "noise.h"

const char* BRAILLE[5][5] = {
    { "⠀", "⢀", "⢠", "⢰", "⢸" },
    { "⡀", "⣀", "⣠", "⣰", "⣸" },
    { "⡄", "⣄", "⣤", "⣴", "⣼" },
    { "⡆", "⣆", "⣦", "⣶", "⣾" },
    { "⡇", "⣇", "⣧", "⣷", "⣿" }
};

int main(int argc, char** argv) {
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int octaves = atoi(argv[3]);
    float lacunarity = atof(argv[4]);
    float gain = atof(argv[5]);
    int noise_values_count = atoi(argv[6]);
    int seed = atoi(argv[7]);
    srandom(seed);
    struct Noise noise;
    noise_init(&noise, noise_values_count);
    char* output[height][width];
    float dx = 1.0 / (float)(width * 2);
    float dy = 1.0 / (float)(height * 4);
    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++) {
            int ix1 = ix * 2;
            int ix2 = ix1 + 1;
            int iy_hi = (height - iy) * 4;
            int iy_lo = iy_hi - 4;
            float y_lo = dy * (float)iy_lo;
            float noise_y1 = noise_lookup(&noise, dx * (float)ix1);
            float t1 = (noise_y1 - y_lo) / (4.f * dy);
            int n1 = t1 >= 1.0 ? 4 : t1 < 0 ? 0 : ((int)(t1 / 0.25) + 1);
            float noise_y2 = noise_lookup(&noise, dx * (float)ix2);
            float t2 = (noise_y2 - y_lo) / (4.f * dy);
            int n2 = t2 >= 1.0 ? 4 : t2 < 0 ? 0 : ((int)(t2 / 0.25) + 1);
            output[iy][ix] = BRAILLE[n1][n2];
        }
    }
    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++)
            printf("%s", output[iy][ix]);
        printf("\n");
    }
    noise_free(&noise);
}
