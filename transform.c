#include <malloc.h>
#include "tarnsform.h"
#include "image.h"
#include "bmp.h"

struct image rotate(image const source) {
    image transform;
    transform.data = malloc(source.height * source.width * sizeof(struct pixel));
    transform.width = source.width;
    transform.height = source.height;
    for (size_t i = 0; i < source.height; ++i) {
        for (size_t j = 0; j < source.width; ++j) {
            transform.data[source.height * j + source.height - i - 1] = source.data[source.width * i + j];
        }
    }
    return (image) {.height = source.width, .width = source.height, .data = transform.data};;

}
