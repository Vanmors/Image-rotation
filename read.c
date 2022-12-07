#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "image.h"
#include "tarnsform.h"

//uint64_t getPadding(bmp_header *bmpFile) {
//    uint64_t byteAllOfPeacture = bmpFile->biBitCount / 8 * bmpFile->biWidth;
//    uint64_t rowPadding = (4 - (byteAllOfPeacture % 4)) % 4;
//    return rowPadding;
//}
uint8_t get_padding(uint32_t width) {
    return 4 - (width * sizeof(struct pixel)) % 4;
}
void bmpWrite(char* filename, image* pixelmap){
    FILE * pFile = fopen (filename, "wb");
    if (pFile == NULL)
        return;

    uint16_t tmpUInt16 = 0;
    //int16_t tmpInt16 = 0;
    uint32_t tmpUInt32 = 0;
    int32_t tmpInt32 = 0;

    /*Структура BITMAPFILEHEADER (14 байт);*/
    /*[0-й байт] Отметка формата;*/
    fputc ('B', pFile);
    fputc ('M', pFile);

    /*[2-й байт] Размер файла (размер заголовка файла + размер изображения * разрядность пикселя);*/
    tmpUInt32 = 14 + 40 + pixelmap -> width * pixelmap -> height * 32;
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

    /*[6-й байт] Зарезервировано;*/
    fputc (0, pFile);
    fputc (0, pFile);
    fputc (0, pFile);
    fputc (0, pFile);

    /*[10-й байт] Положение пиксельных данных относительно начала файла;*/
    tmpUInt32 = 14 + 40;
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);


    /*Структура BITMAPINFO (40 байт);*/
    /*[14-й байт] Размер структуры и по совместительству версия формата;*/
    tmpUInt32 = 40; /*Версия 3;*/
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

    /*[18-й байт] Ширина изображения;*/
    tmpInt32 = (int32_t) pixelmap -> width;
    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);

    /*[22-й байт] Высота изображения;*/
    tmpInt32 = (int32_t) pixelmap -> height;
    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);

    /*[26-й байт] Значение формата;*/
    tmpUInt16 = 1;
    fwrite (&tmpUInt16, sizeof(uint16_t), 1, pFile);

    /*[28-й байт] Бит на пиксель;*/
    tmpUInt16 = 32;
    fwrite (&tmpUInt16, sizeof(uint16_t), 1, pFile);

    /*[30-й байт] Метод компрессии;*/
    tmpUInt32 = 0; /*Без сжатия;*/
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

    /*[34-й байт] Размер пиксельных данных в байтах;*/
    tmpUInt32 = 0; /*Можно обнулить, так как не используется сжатие;*/
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

    /*[38-й байт] PPM по горизонтали;*/
    tmpInt32 = 2835;
    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);

    /*[42-й байт] PPM по вертикали;*/
    tmpInt32 = 2835;
    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);

    /*[46-й байт] Размер таблицы цветов в ячейках;*/
    tmpUInt32 = 0;
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

    /*[50-й байт] Количество ячеек от начала таблицы цветов до последней используемой (включая её саму);*/
    tmpUInt32 = 0;
    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);

}
enum {
    BMP_BF_TYPE = 19778,
    BMP_BF_RESERVED = 0,
    BMP_BO_OFF_BITS = 54,
    BMP_BI_SIZE = 40,
    BMP_FILE_HEADER_SIZE = 14,
    BMP_BI_PLANES = 1,
    BMP_BI_BIT_COUNT = 24,
    BMP_BI_COMPRESSION = 0,
    BMP_BI_X_PELS_PER_METER = 2835,
    BMP_BI_Y_PELS_PER_METER = 2835,
    BMP_BI_CLR_USED = 0,
    BMP_BI_CLR_IMPORTANT = 0,
    BMP_HEADER_SIZE = sizeof(struct bmp_header)
};
static struct bmp_header create_header(struct image *img) {
//    size_t size = img->height * img->width * sizeof(struct pixel);
//    return (struct bmp_header) {.bfType=19778, .bfReserved=0, .bOffBits=sizeof(struct bmp_header),
//            .biPlanes=1, .biCompression=0, .biXPelsPerMeter=2834, .biYPelsPerMeter=2834, .biClrUsed=0, .biClrImportant=0,
//            .biBitCount=24, .biHeight=img->height, .biWidth=img->width,
//            .biSizeImage =size, .bfileSize= sizeof(struct bmp_header) + size, .biSize=40};
    struct bmp_header header = (struct bmp_header) {0};

    size_t row_size = sizeof(struct pixel) * img->width;
    size_t padded_row_size = row_size + get_padding(row_size);
    size_t image_size = padded_row_size * img->height;

    header.bOffBits = BMP_BO_OFF_BITS;
    header.bfReserved = BMP_BF_RESERVED;
    header.bfileSize = image_size + BMP_BO_OFF_BITS;
    header.biBitCount = BMP_BI_BIT_COUNT;
    header.biClrImportant = BMP_BI_CLR_IMPORTANT;
    header.biClrUsed = BMP_BI_CLR_USED;
    header.biCompression = BMP_BI_COMPRESSION;
    header.biHeight = img->height;
    header.biPlanes = BMP_BI_PLANES;
    header.biSize = BMP_HEADER_SIZE - BMP_FILE_HEADER_SIZE;
    header.biSizeImage = image_size;
    header.biWidth = img->width;
    header.biXPelsPerMeter = BMP_BI_X_PELS_PER_METER;
    header.biYPelsPerMeter = BMP_BI_Y_PELS_PER_METER;
    header.bfType = BMP_BF_TYPE;
    return header;
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

//    image image1;
//    int data_size = bmpHeader->biWidth * bmpHeader->biHeight * bmpHeader->biBitCount /
//                    8; // для выделения памяти по массив пикселей
//    image1.data = (struct pixel *) (unsigned char *) malloc(data_size); // выделения памяти под массив с пикселями
    image image1 = createImage(bmpHeader, file);


//    fseek(file, getPadding(bmpHeader), SEEK_CUR);
//    fseek(file, bmpHeader->bOffBits, SEEK_SET);
//    fread(image1.data, bmpHeader->biSizeImage, 1, file);
    uint8_t padding = get_padding(image1.width);

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
    bmp_header bmpWrite = create_header(&image1);
    if (fwrite(&bmpWrite, sizeof(struct bmp_header), 1, out)){
        printf("%s", "error_bmp_write");
    }
//    bmpWrite("C:\\Users\\morik\\CLionProjects\\TestLab3\\out.bmp", &image1);
    for (size_t i = 0; i < image1.height; i++) {
        if (fwrite(image1.data + i * image1.width, sizeof(struct pixel), image1.width, out) != image1.width){
            printf("%s", "error1");
        }

        if (fseek(out, get_padding(image1.width), SEEK_CUR) != 0) {
            printf("%s", "error2");
        }
    }

//

    fclose(out);
//    for (int i = 0; i < bmpHeader->biSizeImage; ++i) {
//        if (i % 16 == 0) {
//            printf("\n%04x: ", i);
//        }
//        printf("%02x ", image1.data[i]);
//    }
    return bmpHeader;

}

void saveFile(bmp_header *bmpHeader, char *fname){
//    FILE *out = fopen(fname, "wb");
//
//    if (fwrite(bmpHeader, sizeof(struct bmp_header), 1, out)){
//        printf("%s", "error");
//    }
//    fclose(out);


}

void freeBMPFile(bmp_header *bmp_file) {
    if (bmp_file) {
        free(bmp_file);
    }
}