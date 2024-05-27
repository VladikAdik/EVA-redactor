#ifndef PALLETECOMMAND_H
#define PALLETECOMMAND_H

#include "image.h"

class paletteCommand {

private:
    int N = 8;///<количество цветов в палитре
    image &picture;///<изображение
    std::vector<pixel>& pixelArr;///<массив пикселей
    std::vector<pixel> finalP;///<итоговые цвета палитры

    std::vector<pixel> backupPixelArr;///<запасной массива пикселей
    int backupW;///<запасное значение ширины
    int backupH;///<запасное значение высоты

    void pallete();///<функция определения палитры

public:
    paletteCommand(image &image);///<конструктор

    std::vector<pixel> getPallete();///<получение итоговые цвета палитры

    std::vector<int> getPalletePriority();///<получение массива принадлежностей пикселей к цветам палитры

};
#endif // PALLETECOMMAND_H
