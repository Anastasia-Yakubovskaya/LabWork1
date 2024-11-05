#ifndef BMPREADER_H
#define BMPREADER_H

#include <cstdint>
#include <string>
#include <vector>

// Структуры для заголовков BMP
#pragma pack(push, 1)

struct BMPHeader {
    uint16_t bfType;      // Тип файла (должен быть "BM")
    uint32_t bfSize;      // Размер файла в байтах
    uint16_t bfReserved1; // Зарезервировано (обычно 0)
    uint16_t bfReserved2; // Зарезервировано (обычно 0)
    uint32_t bfOffBits;   // Смещение до данных пикселей
};

struct BMPInfoHeader {
    uint32_t biSize;          // Размер этого заголовка
    int32_t  biWidth;         // Ширина изображения
    int32_t  biHeight;        // Высота изображения
    uint16_t biPlanes;        // Количество цветовых плоскостей
    uint16_t biBitCount;      // Количество бит на пиксель
    uint32_t biCompression;    // Методы сжатия
    uint32_t biSizeImage;     // Размер данных изображения
    int32_t  biXPelsPerMeter;  // Горизонтальное разрешение
    int32_t  biYPelsPerMeter;  // Вертикальное разрешение
    uint32_t biClrUsed;       // Количество используемых цветов
    uint32_t biClrImportant;   // Количество важных цветов
};

#pragma pack(pop)

// Декларация функций
void readBMP(const std::string& filePath, BMPHeader& bmpHeader, BMPInfoHeader& bmpInfoHeader, std::vector<uint8_t>& pixels);

#endif // BMPREADER_H
