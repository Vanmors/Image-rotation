#ifndef TESTLAB3_IMAGE_H
#define TESTLAB3_IMAGE_H

#include  <stdint.h>
typedef struct image {
    uint64_t width, height;
    struct pixel* data;
} image;

#endif //TESTLAB3_IMAGE_H
