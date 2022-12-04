#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "image.h"


void rowsOfPixels(bmp_header *bmpFile, image *image1, FILE *file) {
    int bytesFroPixel = bmpFile->biBitCount / 8;
    int rowSize = bytesFroPixel * bmpFile->biWidth;
    int rowPadding = (4 - (rowSize % 4)) % 4;
    int rowsWritten = 0;
    unsigned char *row = (unsigned char *) malloc(rowSize + rowPadding);
    unsigned char *p = (unsigned char *) &image1->data[(bmpFile->biHeight - 1) * rowSize];

}

bmp_header *loadBMPFile(char *fname) {
    FILE *file = fopen(fname, "r");
    if (!file) {
        printf("Can't load file \'%s\'\n", fname);
        exit(0);
    }

    bmp_header *bmpHeader = (bmp_header *) malloc(sizeof(bmp_header)); // выделение памяти под файл
    fread(bmpHeader, sizeof(bmp_header), 1, file); // считывание файла

    image image1;
    int data_size = bmpHeader->biWidth * bmpHeader->biHeight * bmpHeader->biBitCount /
                    8; // для выделения памяти по массив пикселей
    image1.data = (struct pixel *) (unsigned char *) malloc(data_size); // выделения памяти под массив с пикселями

//    fseek(file, bmpHeader->bOffBits, SEEK_SET);
//    fread(image1.data, bmpHeader->biSizeImage, 1, file);

    fclose(file);
//    for (int i = 0; i < bmpHeader->biSizeImage; ++i) {
//        if (i % 16 == 0) {
//            printf("\n%04x: ", i);
//        }
//        printf("%02x ", image1.data[i]);
//    }
    return bmpHeader;

}


void freeBMPFile(bmp_header *bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}