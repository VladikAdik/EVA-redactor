#ifndef COLORMASK_H
#define COLORMASK_H

#include "image.h"

class colorMask
{
private:
    image &Image;///<изображение
    std::vector<pixel>& pixelBuffer;///<Массив пикселей
    int r, g, b, ctr;///<значения желаемого красного, зелёного, синего цветов  и контраст

    void colorMaskExec();///<применение цветового фильтра
    int colorDef(int c, int wc);///<определение окончательного цвета пикселя
public:
    colorMask(image &Image, int r, int g, int b, int ctr);///<конструктор класса
};

#endif // COLORMASK_H
