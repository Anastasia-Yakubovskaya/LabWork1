#ifndef GAUSFILTER_H
#define GAUSFILTER_H

#include <vector>
#include <cstdint>

void applyGaussianFilter(const std::vector<uint8_t>& originalPixels, int width, int height, std::vector<uint8_t>& filteredPixels);

#endif // GAUSFILTER_H
