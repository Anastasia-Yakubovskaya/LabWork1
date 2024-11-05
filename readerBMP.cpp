#include "BMPReader.h"
#include <iostream>
#include <fstream>

void readBMP(const std::string& filePath, BMPHeader& bmpHeader, BMPInfoHeader& bmpInfoHeader, std::vector<uint8_t>& pixels) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }
    
    // Чтение заголовка BMP
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));

    if (bmpHeader.bfType != 0x4D42) { // 'BM' в шестнадцатеричной системе
        std::cerr << "Not a BMP file" << std::endl;
        return;
    }

    // Чтение информационного заголовка
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

    // Перемещение указателя на позицию данных пикселей
    file.seekg(bmpHeader.bfOffBits);

    // Вычисление размера изображения
    size_t imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * (bmpInfoHeader.biBitCount / 8);
    pixels.resize(imageSize);

    // Чтение данных пикселей
    file.read(reinterpret_cast<char*>(pixels.data()), imageSize);
    file.close();
}
