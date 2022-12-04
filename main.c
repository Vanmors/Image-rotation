#include <stdio.h>
#include "bmp.h"
#include "image.h"


int main() {
    printf("Hello, World!\n");
    bmp_header *bmpFile = loadBMPFile("C:\\Users\\morik\\CLionProjects\\TestLab3\\input.bmp");
    printf("Size = %d\n", bmpFile->biBitCount);
    printf("Width = %d\n", bmpFile->biSizeImage);
    printf("Height = %d\n", bmpFile->biHeight);
    freeBMPFile(bmpFile);
    return 0;
}

