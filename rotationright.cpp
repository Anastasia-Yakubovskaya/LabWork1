#include "rotationright.h"

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
