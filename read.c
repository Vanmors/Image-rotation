#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "image.h"
#include "tarnsform.h"

uint64_t getPadding(uint32_t width) {
    uint64_t rowPadding = 4 - (width * sizeof(struct pixel)) % 4;
    return rowPadding;
}

static struct bmp_header create_header(image *img, bmp_header bmpHeader) {
    size_t sizeImage = img->height * img->width * sizeof(struct pixel);
    return (struct bmp_header) {.bfType=bmpHeader.bfType,
            .bfReserved=bmpHeader.bfReserved,
            .bOffBits=bmpHeader.bOffBits,
            .biPlanes=bmpHeader.biPlanes,
            .biCompression=bmpHeader.biCompression,
            .biXPelsPerMeter=bmpHeader.biXPelsPerMeter,
            .biYPelsPerMeter=bmpHeader.biYPelsPerMeter,
            .biClrUsed=bmpHeader.biClrUsed,
            .biClrImportant=bmpHeader.biClrImportant,
            .biBitCount=bmpHeader.biBitCount,
            .biHeight=img->height,
            .biWidth=img->width,
            .biSizeImage =sizeImage,
            .bfileSize= bmpHeader.bOffBits + sizeImage,
            .biSize=bmpHeader.biSize};
}

image createImage(bmp_header *bmpHeader, FILE* file){
    image image1;
    int data_size = bmpHeader->biWidth * bmpHeader->biHeight * bmpHeader->biBitCount /8; // для выделения памяти по массив пикселей
    image1.width = bmpHeader->biWidth;
    image1.height = bmpHeader->biHeight;
    image1.data = (struct pixel *) (unsigned char *) malloc(data_size); // выделения памяти под массив с пикселями
//    fseek(file, getPadding(bmpHeader), SEEK_CUR);
    return image1;
}
bmp_header *loadBMPFile(char *fname) {
    FILE *file = fopen(fname, "rb");
    if (!file) {
        printf("Can't load file \'%s\'\n", fname);
        exit(0);
    }

    bmp_header *bmpHeader = (bmp_header *) malloc(sizeof(bmp_header)); // выделение памяти под файл
    fread(bmpHeader, sizeof(bmp_header), 1, file); // считывание файла

    image image1 = createImage(bmpHeader, file);

    uint8_t padding = getPadding(image1.width);

    for (size_t i = 0; i < image1.height; i++) {
        if (fread(image1.data + (i * image1.width), sizeof(struct pixel), image1.width, file) != image1.width) {
            printf("%s", "ok");
        }

        if (fseek(file, padding, SEEK_CUR) != 0) {
            printf("%s", "ok");
        }
    }

    image1 = rotate(image1);




    fclose(file);
    FILE *out = fopen("C:\\Users\\morik\\CLionProjects\\TestLab3\\out.bmp", "w+b");
    bmp_header bmpWrite = create_header(&image1, *bmpHeader);
    if (fwrite(&bmpWrite, sizeof(bmp_header), 1, out)){
        printf("%s", "error_bmp_write");
    }
//    bmpWrite("C:\\Users\\morik\\CLionProjects\\TestLab3\\out.bmp", &image1);
    for (size_t i = 0; i < image1.height; i++) {
        if (fwrite(image1.data + i * image1.width, sizeof(struct pixel), image1.width, out) != image1.width){
            printf("%s", "error1");
        }

        if (fseek(out, getPadding(image1.width), SEEK_CUR) != 0) {
            printf("%s", "error2");
        }
    }

    fclose(out);

    return bmpHeader;

}

void freeBMPFile(bmp_header *bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}