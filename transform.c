//
// Created by morik on 05.12.2022.
//
#include <malloc.h>
#include "tarnsform.h"
#include "image.h"
#include "bmp.h"

struct image rotate(image const source) {
    image transform;
    uint64_t width = source.width;
    uint64_t height = source.height;
    transform.data = malloc(source.height * source.width * sizeof(struct pixel));

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            transform.data[height * j + height - i - 1] = source.data[width * i + j];
//            to->pixels[from->height * j + from->height - i - 1] = from->pixels[from->width * i + j];
        }

    }
    return transform;
}
