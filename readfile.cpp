#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#pragma pack(push, 1)
struct BMPHeader {
    uint16_t bfType;    
    uint32_t bfSize;     
    uint16_t bfReserved1; 
    uint16_t bfReserved2; 
    uint32_t bfOffBits;  
};
struct BMPInfoHeader {
    uint32_t biSize;       
    int32_t  biWidth;        
    int32_t  biHeight;       
    uint16_t biPlanes;      
    uint16_t biBitCount;      
    uint32_t biCompression;    
    uint32_t biSizeImage;     
    int32_t  biXPelsPerMeter; 
    int32_t  biYPelsPerMeter; 
    uint32_t biClrUsed;      
    uint32_t biClrImportant;   
};
#pragma pack(pop)
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
void rotateRight(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& rotatedPixels) {
    int newWidth = height;
    int newHeight = width;
    rotatedPixels.resize(newWidth * newHeight * 3); // RGB
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 0]= originalPixels[(i * width + j) * 3 + 0]; // R
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 1]= originalPixels[(i * width + j) * 3 + 1]; // G
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 2]= originalPixels[(i * width + j) * 3 + 2]; // B
        }
    }
}
void rotateLeft(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& rotatedPixels) {
    int newWidth = height;
    int newHeight = width;
    rotatedPixels.resize(newWidth * newHeight * 3); // RGB
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            rotatedPixels[(j * newWidth + (newWidth - i - 1)) * 3 + 0] = originalPixels[(i * width + j) * 3 + 0]; // R
            rotatedPixels[(j * newWidth + (newWidth - i - 1)) * 3 + 1] = originalPixels[(i * width + j) * 3 + 1]; // G
            rotatedPixels[(j * newWidth + (newWidth - i - 1)) * 3 + 2] = originalPixels[(i * width + j) * 3 + 2]; // B
        }
    }
}
int main() {
    std::string inputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp"; 
    std::string outputFilePathRight = "/home/anastasya/Документы/LabWork/LabWork1/rotated_right.bmp"; 
    std::string outputFilePathLeft = "/home/anastasya/Документы/LabWork/LabWork1/rotated_left.bmp"; 

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    
    std::vector<uint8_t> pixels;
    readBMP(inputFilePath, bmpHeader, bmpInfoHeader, pixels);
    
    std::vector<uint8_t> rotatedPixelsRight;
    rotateRight(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsRight);
    
    bmpInfoHeader.biWidth = bmpInfoHeader.biHeight;
    bmpInfoHeader.biHeight = bmpInfoHeader.biWidth;
    
    writeBMP(outputFilePathRight, bmpHeader, bmpInfoHeader, rotatedPixelsRight);
    
    std::vector<uint8_t> rotatedPixelsLeft;
    rotateLeft(pixels, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, rotatedPixelsLeft);
    
    bmpInfoHeader.biWidth = bmpInfoHeader.biHeight;
    bmpInfoHeader.biHeight = bmpInfoHeader.biWidth;
    
    writeBMP(outputFilePathLeft, bmpHeader, bmpInfoHeader, rotatedPixelsLeft);
    
    std::cout << "Created rotated BMP files: " << outputFilePathRight << " and " << outputFilePathLeft << std::endl;
    
    return 0;
}

