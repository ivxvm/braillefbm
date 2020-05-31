#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "noise.h"
#include "fbm.h"

char* BRAILLE[5][5] = {
    { "⠀", "⢀", "⢠", "⢰", "⢸" },
    { "⡀", "⣀", "⣠", "⣰", "⣸" },
    { "⡄", "⣄", "⣤", "⣴", "⣼" },
    { "⡆", "⣆", "⣦", "⣶", "⣾" },
    { "⡇", "⣇", "⣧", "⣷", "⣿" }
};

float noise_lookup_cb(void* ctx, float x) {
    return noise_lookup((struct Noise*) ctx, x);
}

int main(int argc, char** argv) {
    int width;
    int height;
    int octaves;
    float lacunarity;
    float gain;
    int noise_values_count;
    int seed;
    if (argc == 1) {
        srand(time(NULL));
        width = 40 + rand() % 31;
        height = 10 + rand() % 31;
        octaves = 2 + rand() % 3;
        lacunarity = ((float)(rand() % 1000) / 1000.0) * 10.0;
        gain = (float)(10 + rand() % 71) / 100.0;
        noise_values_count = 2 + rand() % (width - 1);
        seed = rand();
    } else if (argc == 8) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        octaves = atoi(argv[3]);
        lacunarity = atof(argv[4]);
        gain = atof(argv[5]);
        noise_values_count = atoi(argv[6]);
        seed = atoi(argv[7]);
    } else {
        printf("braillefbm <width> <height> <octaves> <lacunarity> <gain> <noise_values_count> <seed>\n");
        return 1;
    }
    printf("./braillefbm %d %d %d %f %f %d %d\n", width, height, octaves, lacunarity, gain, noise_values_count, seed);
    srand(seed);
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
            float noise_y1 = fbm(octaves, lacunarity, gain, dx * (float)ix1, noise_lookup_cb, &noise);
            float t1 = (noise_y1 - y_lo) / (4.f * dy);
            int n1 = t1 >= 1.0 ? 4 : t1 < 0 ? 0 : ((int)(t1 / 0.25) + 1);
            float noise_y2 = fbm(octaves, lacunarity, gain, dx * (float)ix2, noise_lookup_cb, &noise);
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
    return 0;
}
