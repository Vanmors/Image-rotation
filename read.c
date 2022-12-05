#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "image.h"

uint64_t getPadding(bmp_header *bmpFile) {
    uint64_t byteAllOfPeacture = bmpFile->biBitCount / 8 * bmpFile->biWidth;
    uint64_t rowPadding = (4 - (byteAllOfPeacture % 4)) % 4;
    return rowPadding;
}
image createImage(bmp_header *bmpHeader, FILE* file){
    image image1;
    int data_size = bmpHeader->biWidth * bmpHeader->biHeight * bmpHeader->biBitCount /
                    8; // для выделения памяти по массив пикселей
    image1.data = (struct pixel *) (unsigned char *) malloc(data_size); // выделения памяти под массив с пикселями
    fseek(file, getPadding(bmpHeader), SEEK_CUR);
    return image1;
}
bmp_header *loadBMPFile(char *fname) {
    FILE *file = fopen(fname, "r");
    if (!file) {
        printf("Can't load file \'%s\'\n", fname);
        exit(0);
    }

    bmp_header *bmpHeader = (bmp_header *) malloc(sizeof(bmp_header)); // выделение памяти под файл
    fread(bmpHeader, sizeof(bmp_header), 1, file); // считывание файла

//    image image1;
//    int data_size = bmpHeader->biWidth * bmpHeader->biHeight * bmpHeader->biBitCount /
//                    8; // для выделения памяти по массив пикселей
//    image1.data = (struct pixel *) (unsigned char *) malloc(data_size); // выделения памяти под массив с пикселями
    image image1 = createImage(bmpHeader, file);


//    fseek(file, getPadding(bmpHeader), SEEK_CUR);
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