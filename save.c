//#include <stdint.h>
//#include <stdio.h>
//#include "bmp.h"
//
///*Сохранение pixelmap в .bmp-файл;*/
//void impl_saveBMP (IMPL_PIXELMAP * pixelmap, const char * filename) {
//
//    FILE * pFile = fopen (filename, "wb");
//    if (pFile == NULL)
//        return;
//
//    uint16_t tmpUInt16 = 0;
//    //int16_t tmpInt16 = 0;
//    uint32_t tmpUInt32 = 0;
//    int32_t tmpInt32 = 0;
//
//    /*Структура BITMAPFILEHEADER (14 байт);*/
//    /*[0-й байт] Отметка формата;*/
//    fputc ('B', pFile);
//    fputc ('M', pFile);
//
//    /*[2-й байт] Размер файла (размер заголовка файла + размер изображения * разрядность пикселя);*/
//    tmpUInt32 = 14 + 40 + pixelmap -> width * pixelmap -> height * 32;
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//    /*[6-й байт] Зарезервировано;*/
//    fputc (0, pFile);
//    fputc (0, pFile);
//    fputc (0, pFile);
//    fputc (0, pFile);
//
//    /*[10-й байт] Положение пиксельных данных относительно начала файла;*/
//    tmpUInt32 = 14 + 40;
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//
//    /*Структура BITMAPINFO (40 байт);*/
//    /*[14-й байт] Размер структуры и по совместительству версия формата;*/
//    tmpUInt32 = 40; /*Версия 3;*/
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//    /*[18-й байт] Ширина изображения;*/
//    tmpInt32 = (int32_t) pixelmap -> width;
//    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);
//
//    /*[22-й байт] Высота изображения;*/
//    tmpInt32 = (int32_t) pixelmap -> height;
//    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);
//
//    /*[26-й байт] Значение формата;*/
//    tmpUInt16 = 1;
//    fwrite (&tmpUInt16, sizeof(uint16_t), 1, pFile);
//
//    /*[28-й байт] Бит на пиксель;*/
//    tmpUInt16 = 32;
//    fwrite (&tmpUInt16, sizeof(uint16_t), 1, pFile);
//
//    /*[30-й байт] Метод компрессии;*/
//    tmpUInt32 = 0; /*Без сжатия;*/
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//    /*[34-й байт] Размер пиксельных данных в байтах;*/
//    tmpUInt32 = 0; /*Можно обнулить, так как не используется сжатие;*/
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//    /*[38-й байт] PPM по горизонтали;*/
//    tmpInt32 = 2835;
//    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);
//
//    /*[42-й байт] PPM по вертикали;*/
//    tmpInt32 = 2835;
//    fwrite (&tmpInt32, sizeof(int32_t), 1, pFile);
//
//    /*[46-й байт] Размер таблицы цветов в ячейках;*/
//    tmpUInt32 = 0;
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//    /*[50-й байт] Количество ячеек от начала таблицы цветов до последней используемой (включая её саму);*/
//    tmpUInt32 = 0;
//    fwrite (&tmpUInt32, sizeof(uint32_t), 1, pFile);
//
//
//    /*[54-й байт] Пиксельные данные;*/
//    size_t i = 0;
//    for (; i < pixelmap -> width * pixelmap -> height; ++i) {
//        fwrite (&(pixelmap -> data[i].b), sizeof(uint8_t), 1, pFile);
//        fwrite (&(pixelmap -> data[i].g), sizeof(uint8_t), 1, pFile);
//        fwrite (&(pixelmap -> data[i].r), sizeof(uint8_t), 1, pFile);
//        fwrite (&(pixelmap -> data[i].a), sizeof(uint8_t), 1, pFile);
//    }
//
//    fclose (pFile);
//
//}