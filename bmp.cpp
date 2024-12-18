/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/
#include "bmp.h"
#include <algorithm>
#include <cmath>

bool BMPImage::read(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

    size_t imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * (bmpInfoHeader.biBitCount / 8);
    pixels.resize(imageSize);
    
    file.seekg(bmpHeader.bfOffBits);
    file.read(reinterpret_cast<char*>(pixels.data()), imageSize);
    
    file.close();
    return true;
}

bool BMPImage::write(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
    
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    
    file.close();
    return true;
}

void BMPImage::rotateRight() {
   int width = bmpInfoHeader.biWidth;
   int height = bmpInfoHeader.biHeight;

   std::vector<uint8_t> rotatedPixels(height * width * 3); // RGB

   for (int i = 0; i < width; ++i) {
       for (int j = 0; j < height; ++j) {
           rotatedPixels[((j * width) + (width - i - 1)) * 3 + 0] = pixels[(i * height + j) * 3 + 0]; // R
           rotatedPixels[((j * width) + (width - i - 1)) * 3 + 1] = pixels[(i * height + j) * 3 + 1]; // G
           rotatedPixels[((j * width) + (width - i - 1)) * 3 + 2] = pixels[(i * height + j) * 3 + 2]; // B
       }
   }

   std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); // Меняем ширину и высоту
   pixels = std::move(rotatedPixels); // Обновляем пиксели
}

void BMPImage::rotateLeft() {
   int width = bmpInfoHeader.biWidth;
   int height = bmpInfoHeader.biHeight;

   std::vector<uint8_t> rotatedPixels(height * width * 3); // RGB

   for (int i = 0; i < width; ++i) {
       for (int j = 0; j < height; ++j) {
           rotatedPixels[(height - j - 1) * width * 3 + i * 3 + 0] = pixels[(i * height + j) * 3 + 0]; // R
           rotatedPixels[(height - j - 1) * width * 3 + i * 3 + 1] = pixels[(i * height + j) * 3 + 1]; // G
           rotatedPixels[(height - j - 1) * width * 3 + i * 3 + 2] = pixels[(i * height + j) * 3 + 2]; // B
       }
   }

   std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); // Меняем ширину и высоту
   pixels = std::move(rotatedPixels); // Обновляем пиксели
}

void BMPImage::applyGaussianFilter() {
   float kernel[5][5] = {  
       {1/273.0f,4/273.0f,6/273.0f,4/273.0f,1/273.0f},  
       {4/273.0f,16/273.0f,24/273.0f,16/273.0f,4/273.0f},  
       {6/273.0f,24/273.0f,36/273.0f,24/273.0f,6/273.0f},  
       {4/273.0f,16/273.0f,24/273.0f,16/273.0f,4/273.0f},  
       {1/273.0f,4/273.0f,6/273.0f,4/273.0f,1/273.0f}  
   };  

   std::vector<uint8_t> filteredPixels(pixels.size());  

   for (int y = 2; y < bmpInfoHeader.biHeight - 2; ++y) {  
       for (int x = 2; x < bmpInfoHeader.biWidth - 2; ++x) {  
           float r = 0, g = 0, b = 0;

           for (int ky = -2; ky <= 2; ++ky) {  
               for (int kx = -2; kx <= 2; ++kx) {  
                   int pixelIndex = ((y + ky) * bmpInfoHeader.biWidth + (x + kx)) * 3;  
                   r += pixels[pixelIndex]     * kernel[ky + 2][kx + 2];  
                   g += pixels[pixelIndex + 1] * kernel[ky + 2][kx + 2];  
                   b += pixels[pixelIndex + 2] * kernel[ky + 2][kx + 2];  
               }  
           }  

           int filteredIndex = (y * bmpInfoHeader.biWidth + x) * 3;  
           filteredPixels[filteredIndex]     = static_cast<uint8_t>(std::min(std::max(int(r),   0),255));  
           filteredPixels[filteredIndex + 1] = static_cast<uint8_t>(std::min(std::max(int(g),   0),255));  
           filteredPixels[filteredIndex + 2] = static_cast<uint8_t>(std::min(std::max(int(b),   0),255));  
       }  
   }  

   pixels.swap(filteredPixels); 
}


