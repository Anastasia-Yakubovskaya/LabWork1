#include <iostream>
#include <fstream>
#include <vector>

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

void readBMP(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
 
    BMPHeader bmpHeader;
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));

    BMPInfoHeader bmpInfoHeader;
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
    
    std::cout << "Width: " << bmpInfoHeader.biWidth << std::endl;
    std::cout << "Height: " << bmpInfoHeader.biHeight << std::endl;
    std::cout << "Bit Count: " << bmpInfoHeader.biBitCount << std::endl;

    file.seekg(bmpHeader.bfOffBits);
    

    size_t imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * (bmpInfoHeader.biBitCount / 8);
    std::vector<uint8_t> pixels(imageSize);
    
    file.read(reinterpret_cast<char*>(pixels.data()), imageSize);

    file.close();
}

int main() {
    std::string filePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp"; 
    readBMP(filePath);
    return 0;
}
