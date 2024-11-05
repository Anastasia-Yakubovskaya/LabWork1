#include <iostream>
#include "reader.h"
#include "writer.h"
#include "rotationright.h"
#include "rotationleft.h"
#include "gausfilter.h"

int main() {
    std::string inputFilePath = "Airplane.bmp"; 
    std::string outputFilePathRight = "rotated_right.bmp"; 
    std::string outputFilePathLeft = "rotated_left.bmp"; 
    std::string outputFilePathFiltered = "filtered.bmp";

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;

    std::vector<uint8_t> pixels;
    readBMP(inputFilePath, bmpHeader, bmpInfoHeader, pixels);
    
    std::vector<uint8_t> rotatedPixelsRight;
    rotateRight(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsRight);
    
    std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    writeBMP(outputFilePathRight, bmpHeader, bmpInfoHeader, rotatedPixelsRight);
    
    std::vector<uint8_t> rotatedPixelsLeft;
    rotateLeft(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsLeft);
    
    std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    writeBMP(outputFilePathLeft, bmpHeader, bmpInfoHeader, rotatedPixelsLeft);
    
    std::vector<uint8_t> filteredPixels;
    applyGaussianFilter(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, filteredPixels);
    writeBMP(outputFilePathFiltered, bmpHeader, bmpInfoHeader, filteredPixels);
    
    std::cout << "Processing complete!" << std::endl;
    
    return 0;
}
