#include  <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct bmp_header {
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits; // положение данных о пикселях отсносительно начала файла
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount; //кол-во бит на пиксель
    uint32_t biCompression;
    uint32_t biSizeImage; //для выделения памяти под массив пикселей
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
} bmp_header;
#pragma pack(pop)

struct pixel { uint8_t b, g, r; };

uint64_t getPadding(bmp_header *bmpFile);
bmp_header* loadBMPFile(char* fname);
void freeBMPFile(bmp_header* bmp_file);