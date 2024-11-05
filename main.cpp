int main() {
    std::string inputFilePath = "/home/anastasya/Документы/LabWork/LabWork1/Airplane.bmp"; // Укажите путь к вашему BMP файлу
    std::string outputFilePath = "test1.bmp"; // Путь для создания нового BMP файла

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;
    std::vector<uint8_t> pixels;

    // Чтение BMP файла
    readBMP(inputFilePath, bmpHeader, bmpInfoHeader, pixels);

    // Создание нового BMP файла
    writeBMP(outputFilePath, bmpHeader, bmpInfoHeader, pixels);

    std::cout << "Created BMP file: " << outputFilePath << std::endl;

    return 0;
}
