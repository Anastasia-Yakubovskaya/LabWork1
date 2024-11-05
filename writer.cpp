#include "writer.h"
#include <fstream>

void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels) {
    std::ofstream file(filePath, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    file.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    file.close();
}
