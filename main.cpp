#include <iostream> 
#include "bmp.h" 
#include "image_processing.h" 
int main() { 
    std::string inputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp";  
    std::string outputFilePathRight = "/home/anastasya/Документы/LabWork/LabWork1/rotated_right.bmp";  
    std::string outputFilePathLeft = "/home/anastasya/Документы/LabWork/LabWork1/rotated_left.bmp";  
    std::string outputFilePathFilteredRight = "/home/anastasya/Документы/LabWork/LabWork1/filtered_rotated_right.bmp"; 
    std::string outputFilePathFilteredLeft = "/home/anastasya/Документы/LabWork/LabWork1/filtered_rotated_left.bmp"; 
    BMPHeader bmpHeader; 
    BMPInfoHeader bmpInfoHeader; 
    std::vector<uint8_t> pixels; 
    readBMP(inputFilePath, bmpHeader, bmpInfoHeader, pixels); 
     
    // Поворот вправо 
    std::vector<uint8_t> rotatedPixelsRight; 
    rotateRight(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsRight); 
     
    // Сохранение перевернутого изображения вправо 
    std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); 
    writeBMP(outputFilePathRight, bmpHeader, bmpInfoHeader, rotatedPixelsRight); 
     
    // Применение фильтра Гаусса к перевернутому вправо 
    std::vector<uint8_t> filteredPixelsRight; 
    applyGaussianFilter(rotatedPixelsRight, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, filteredPixelsRight); 
    writeBMP(outputFilePathFilteredRight, bmpHeader, bmpInfoHeader, filteredPixelsRight); 
     
    // Поворот влево 
    std::vector<uint8_t> rotatedPixelsLeft; 
    rotateLeft(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsLeft); 
     
    // Сохранение перевернутого изображения влево 
    std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); 
    writeBMP(outputFilePathLeft, bmpHeader, bmpInfoHeader, rotatedPixelsLeft); 
     
    // Применение фильтра Гаусса к перевернутому влево 
    std::vector<uint8_t> filteredPixelsLeft; 
    applyGaussianFilter(rotatedPixelsLeft, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, filteredPixelsLeft); 
    writeBMP(outputFilePathFilteredLeft, bmpHeader, bmpInfoHeader, filteredPixelsLeft); 
    return 0; 
}
