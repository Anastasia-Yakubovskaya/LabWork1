#ifndef BMP_H 
#define BMP_H 
#include <string> 
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
void readBMP(const std::string& filePath, BMPHeader& bmpHeader, BMPInfoHeader& bmpInfoHeader, std::vector<uint8_t>& pixels); 
void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels); 
#endif // BMP_H
