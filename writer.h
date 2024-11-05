#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <vector>
#include <cstdint>
#include "reader.h"

void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels);

#endif 
