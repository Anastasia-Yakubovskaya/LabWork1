
#ifndef BMPWRITER_H
#define BMPWRITER_H

#include "BMPReader.h"

// Декларация функции записи BMP
void writeBMP(const std::string& filePath, const BMPHeader& bmpHeader, const BMPInfoHeader& bmpInfoHeader, const std::vector<uint8_t>& pixels);

#endif // BMPWRITER_H
