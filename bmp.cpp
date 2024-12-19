#include "bmp.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

bool BMPImage::read(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));

    if (bmpHeader.bfType != 0x4D42) { 
        std::cerr << filename << " is not a valid BMP file." << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

    if (bmpInfoHeader.biBitCount != 24) {
        std::cerr << filename << " uses " << bmpInfoHeader.biBitCount 
                  << " bits per pixel (only 24 bit is supported)." << std::endl;
        return false;
    }

    if (bmpInfoHeader.biCompression != 0) {
        std::cerr << filename << " is compressed. "
                  << "Only uncompressed images are supported." << std::endl;
        return false;
    }

    size_t imageSize = bmpInfoHeader.biWidth * bmpInfoHeader.biHeight * (bmpInfoHeader.biBitCount / 8);
    pixels.resize(imageSize);

    file.seekg(bmpHeader.bfOffBits, std::ios::beg);

    for (int row = bmpInfoHeader.biHeight - 1; row >= 0; --row) {
        file.read(reinterpret_cast<char*>(pixels.data() + (row * bmpInfoHeader.biWidth * 3)), bmpInfoHeader.biWidth * 3);
        
        size_t padding = (4 - (bmpInfoHeader.biWidth * 3) % 4) % 4;
        file.ignore(padding);
    }

    file.close();
    return true;
}

bool BMPImage::write(const std::string &filename) const {
   std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);

   if (file.fail()) {
       std::cerr << filename << " cannot be opened for writing." << std::endl;
       return false; 
   }

   if (!(bmpInfoHeader.biWidth > 0 && bmpInfoHeader.biHeight > 0)) {
       std::cerr << "Bitmap cannot be saved. It is not a valid image." << std::endl;
       return false; 
   }

   file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
   file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

   file.seekp(bmpHeader.bfOffBits, std::ios::beg);

   for (int row = bmpInfoHeader.biHeight - 1; row >= 0; --row) {
       std::vector<uint8_t> bytesRow(bmpInfoHeader.biWidth * 3);
       std::copy(pixels.begin() + (row * bmpInfoHeader.biWidth * 3),
                 pixels.begin() + ((row + 1) * bmpInfoHeader.biWidth * 3),
                 bytesRow.begin());

       file.write(reinterpret_cast<char*>(bytesRow.data()), bmpInfoHeader.biWidth * 3);

       size_t padding = (4 - (bmpInfoHeader.biWidth * 3) % 4) % 4;
       for (size_t i = 0; i < padding; i++) {
           file.put(0);
       }
   }

   file.close();
   return true; 
}

void BMPImage::rotateRight() {
   int originalWidth = bmpInfoHeader.biWidth;
   int originalHeight = bmpInfoHeader.biHeight;

   std::vector<uint8_t> rotatedPixels(originalHeight * originalWidth * 3); // RGB

   for (int y = 0; y < originalHeight; ++y) {
       for (int x = 0; x < originalWidth; ++x) {
           int oldIndex = (y * originalWidth + x) * 3;
           int newIndex = ((x) * originalHeight + (originalHeight - y - 1)) * 3;

           rotatedPixels[newIndex]     = pixels[oldIndex];     // R
           rotatedPixels[newIndex + 1] = pixels[oldIndex + 1]; // G
           rotatedPixels[newIndex + 2] = pixels[oldIndex + 2]; // B
       }
   }

   std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); 
   pixels = std::move(rotatedPixels); 
}

void BMPImage::rotateLeft() {
   int originalWidth = bmpInfoHeader.biWidth;
   int originalHeight = bmpInfoHeader.biHeight;

   std::vector<uint8_t> rotatedPixels(originalHeight * originalWidth * 3); // RGB

   for (int y = 0; y < originalHeight; ++y) {
       for (int x = 0; x < originalWidth; ++x) {
           int oldIndex = (y * originalWidth + x) * 3;
           int newIndex = ((originalWidth - x - 1) * originalHeight + y) * 3;

           rotatedPixels[newIndex]     = pixels[oldIndex];     // R
           rotatedPixels[newIndex + 1] = pixels[oldIndex + 1]; // G
           rotatedPixels[newIndex + 2] = pixels[oldIndex + 2]; // B
       }
   }

   std::swap(bmpInfoHeader.biWidth, bmpInfoHeader.biHeight); 
   pixels = std::move(rotatedPixels); 
}


void BMPImage::applyGaussianFilter(int kernelSize) {
    if (kernelSize % 2 == 0 || kernelSize < 3 || kernelSize > 11) {
        std::cerr << "Kernel size must be an odd number between 3 and 11." << std::endl;
        return;
    }

    float sigma = 1.0f; 
    float sum = 0.0f;


    std::vector<std::vector<float>> kernel(kernelSize, std::vector<float>(kernelSize));

    for (int x = -kernelSize / 2; x <= kernelSize / 2; ++x) {
        for (int y = -kernelSize / 2; y <= kernelSize / 2; ++y) {
            float value = (1 / (2 * M_PI * sigma * sigma)) * 
                          exp(-(x*x + y*y) / (2 * sigma * sigma));
            kernel[x + kernelSize / 2][y + kernelSize / 2] = value;
            sum += value;
        }
    }


    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }

    int width = bmpInfoHeader.biWidth;
    int height = bmpInfoHeader.biHeight;

    if (width < kernelSize || height < kernelSize) {
        std::cerr << "Image too small for Gaussian filter" << std::endl;
        return;
    }

    std::vector<uint8_t> filteredPixels(pixels.size());


    for (int y = kernelSize / 2; y < height - kernelSize / 2; ++y) {
        for (int x = kernelSize / 2; x < width - kernelSize / 2; ++x) {
            float r = 0, g = 0, b = 0;

            for (int ky = -kernelSize / 2; ky <= kernelSize / 2; ++ky) {
                for (int kx = -kernelSize / 2; kx <= kernelSize / 2; ++kx) {
                    int pixel_x = x + kx;
                    int pixel_y = y + ky;

                    int pixelIndex = (pixel_y * width + pixel_x) * 3;

                    
                    if (pixelIndex >= 0 && static_cast<size_t>(pixelIndex + 2) < pixels.size()) {
                        r += pixels[pixelIndex]     * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                        g += pixels[pixelIndex + 1] * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                        b += pixels[pixelIndex + 2] * kernel[ky + kernelSize / 2][kx + kernelSize / 2];
                    }
                }
            }

            int filteredIndex = (y * width + x) * 3;
            filteredPixels[filteredIndex]     = static_cast<uint8_t>(std::clamp(int(r),   0,255));
            filteredPixels[filteredIndex + 1] = static_cast<uint8_t>(std::clamp(int(g),   0,255));
            filteredPixels[filteredIndex + 2] = static_cast<uint8_t>(std::clamp(int(b),   0,255));
        }
    }

    pixels.swap(filteredPixels);
}

