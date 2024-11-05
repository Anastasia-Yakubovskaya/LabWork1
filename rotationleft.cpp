#include "rotationleft.h"

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
