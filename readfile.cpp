#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath> 

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

// Функция для поворота вправо
void rotateRight(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& rotatedPixels) {
    int newWidth = height;
    int newHeight = width;
    rotatedPixels.resize(newWidth * newHeight * 3); // RGB
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 0] = originalPixels[(i * width + j) * 3 + 0]; // R
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 1] = originalPixels[(i * width + j) * 3 + 1]; // G
            rotatedPixels[((newHeight - j - 1) * newWidth + i) * 3 + 2] = originalPixels[(i * width + j) * 3 + 2]; // B
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

void applyGaussianFilter(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& filteredPixels) {
    float kernel[3][3] = {
        { 1/16.0f, 2/16.0f, 1/16.0f },
        { 2/16.0f, 4/16.0f, 2/16.0f },
        { 1/16.0f, 2/16.0f, 1/16.0f }
    };
    
    filteredPixels.resize(originalPixels.size());

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float r = 0, g = 0, b = 0;
         
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int pixelIndex = ((y + ky) * width + (x + kx)) * 3;
                    r += originalPixels[pixelIndex + 0] * kernel[ky + 1][kx + 1];
                    g += originalPixels[pixelIndex + 1] * kernel[ky + 1][kx + 1];
                    b += originalPixels[pixelIndex + 2] * kernel[ky + 1][kx + 1];
                }
            }
            int filteredIndex = (y * width + x) * 3;
            filteredPixels[filteredIndex + 0] = static_cast<uint8_t>(std::min(std::max(int(r), 0), 255));
            filteredPixels[filteredIndex + 1] = static_cast<uint8_t>(std::min(std::max(int(g), 0), 255));
            filteredPixels[filteredIndex + 2] = static_cast<uint8_t>(std::min(std::max(int(b), 0), 255));
        }
    }
}

int main() {
    std::string inputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp"; 
    std::string outputFilePathRight = "/home/anastasya/Документы/LabWork/LabWork1/rotated_right.bmp"; 
    std::string outputFilePathLeft = "/home/anastasya/Документы/LabWork/LabWork1/rotated_left.bmp"; 
    std::string outputFilePathFiltered = "/home/anastasya/Документы/LabWork/LabWork1/filtered.bmp";

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
    


    return 0;
}
  
