/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/
#include "bmp.h" 
#include <fstream> 
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
void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels) { 
    std::ofstream file(filePath, std::ios::binary); 
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader)); 
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader)); 
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size()); 
    file.close(); 
}
