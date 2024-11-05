#include "reader.h"
#include <fstream>
#include <stdexcept>

void readBMP(const std::string& filePath, BMPHeader& bmpHeader, BMPInfoHeader& bmpInfoHeader, std::vector<uint8_t>& pixels) {
    std::ifstream file(filePath, std::ios::binary);
    
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
    file.seekg(bmpHeader.bfOffBits);
    
    size_t imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * (bmpInfoHeader.biBitCount / 8);
    pixels.resize(imageSize);
    file.read(reinterpret_cast<char*>(pixels.data()), imageSize); 
    file.close();
}
