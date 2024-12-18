/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/
#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

#pragma pack(push, 1) // Устанавливаем выравнивание в 1 байт

struct BMPHeader {
    uint16_t bfType;      // Тип файла (должен быть 'BM')
    uint32_t bfSize;      // Размер файла в байтах
    uint16_t bfReserved1; // Зарезервировано
    uint16_t bfReserved2; // Зарезервировано
    uint32_t bfOffBits;   // Смещение до начала данных изображения
};

struct BMPInfoHeader {
    uint32_t biSize;          // Размер этого заголовка
    int32_t biWidth;          // Ширина изображения
    int32_t biHeight;         // Высота изображения
    uint16_t biPlanes;        // Количество цветовых плоскостей
    uint16_t biBitCount;      // Количество бит на пиксель
    uint32_t biCompression;   // Тип сжатия
    uint32_t biSizeImage;     // Размер данных изображения
    int32_t biXPelsPerMeter;   // Горизонтальное разрешение
    int32_t biYPelsPerMeter;   // Вертикальное разрешение
    uint32_t biClrUsed;       // Количество используемых цветов
    uint32_t biClrImportant;  // Количество важных цветов
};

#pragma pack(pop) // Возвращаем выравнивание по умолчанию

class BMPImage {
public:
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    std::vector<uint8_t> pixels;

    BMPImage() {}

    bool read(const std::string& filePath);
    bool write(const std::string& filePath) const;

    void rotateRight();
    void rotateLeft();
    void applyGaussianFilter();
};

#endif // BMP_H


