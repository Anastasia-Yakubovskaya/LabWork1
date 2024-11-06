#ifndef IMAGE_PROCESSING_H 
#define IMAGE_PROCESSING_H 
#include <vector> 
#include <cstdint> 
void rotateRight(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& rotatedPixels); 
void rotateLeft(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& rotatedPixels); 
void applyGaussianFilter(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& filteredPixels); 
#endif // IMAGE_PROCESSING_H
