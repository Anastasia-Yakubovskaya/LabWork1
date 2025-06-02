/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/
#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

#pragma pack(push, 1)


struct BMPHeader
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};


struct BMPInfoHeader
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)


class BMPImage
{
public:
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    std::vector<uint8_t> pixels;

    BMPImage() {}

    bool read(const std::string& filePath);
    bool write(const std::string& filePath) const;

    void rotateRight();
    void rotateLeft();
    void applyGaussianFilter(int kernelSize = 3);
};

#endif // BMP_H

