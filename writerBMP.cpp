#include "BMPWriter.h"
#include <iostream>
#include <fstream>

void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error creating file: " << filePath << std::endl;
        return;
    }

    // Запись заголовка и информационного заголовка
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

    // Запись данных пикселей
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    file.close();
}
