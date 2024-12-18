/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/

#include <iostream>
#include "bmp.h"


int main() { 
     BMPImage image;

     if (!image.read("Airplane.bmp")) {
         std::cerr << "Ошибка чтения файла!" << std::endl;
         return EXIT_FAILURE;
     }

     // Поворот влево и сохранение результата
     image.rotateLeft();
     image.write("rotated_left.bmp");

     // Поворот вправо дважды и сохранение результатов
     image.rotateRight(); 
     image.rotateRight(); 
     image.write("rotated_right_second.bmp");

     // Применение гауссового фильтра к обоим сохраненным изображениям

     BMPImage leftImage;
     leftImage.read("rotated_left.bmp");
     leftImage.applyGaussianFilter();
     leftImage.write("filtered_rotated_left.bmp");

     BMPImage rightSecondImage;
     rightSecondImage.read("rotated_right_second.bmp");
     rightSecondImage.applyGaussianFilter();
     rightSecondImage.write("filtered_rotated_right_second.bmp");

     return EXIT_SUCCESS;
}


