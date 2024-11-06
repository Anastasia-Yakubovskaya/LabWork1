#include "image_processing.h" 
#include <algorithm> 
#include <cmath> 
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
