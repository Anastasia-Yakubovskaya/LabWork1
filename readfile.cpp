
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> // Включаем для использования uint8_t

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

int main() {
    std::string inputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp"; // Укажите путь к вашему BMP файлу
    std::string outputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/test1.bmp"; // Путь для создания нового BMP файла

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    std::vector<uint8_t> pixels;

    // Чтение BMP файла
    readBMP(inputFilePath, bmpHeader, bmpInfoHeader, pixels);

    // Создание нового BMP файла
    writeBMP(outputFilePath, bmpHeader, bmpInfoHeader, pixels);

    std::cout << "Created BMP file: " << outputFilePath << std::endl;

    return 0;
}
