#include "colormask.h"
/*!
* Конструктор для подачи переменных в класс colorMask
* Вызывает функцию применения цветового фильтра
*
* \param image - изображение
* \param r - значение красного оттенка желаемого цвета
* \param g - значение зелёного оттенка желаемого цвета
* \param b - значение синего оттенка желаемого цвета
* \param ctr - значение контраста желаемого цвета
*/
colorMask::colorMask(image &Image, int r, int g, int b, int ctr):
    Image(Image), r(r), g(g), b(b), ctr(ctr), pixelBuffer(Image.getPixelArr()){
    colorMaskExec();
}

/*!
* \brief Функция для применения цветового фильтра на изображение
*
* Изначально весь массив пикселей меняется в серый цвет
* Затем серое изображение перекрашивается в один цвет, который был задан пользователем ползунками. Новые значения r, g, b пикселя определяются в функции colorDef.
* После перекраски изображения применяется алгоритм применения контрастности на изображение. Определяется средняя яркость всех пикселей, рассчитывается коэффициент коррекции по значению, заданному пользователем. По коэффициенту и средней яркости рассчитывается изменение каждого из спектров r, g, b.
*/
void colorMask::colorMaskExec() {
    //Серая картинка
    for (int i = 0; i < Image.getSize(); i++) {
        int gray = (pixelBuffer[i].getR() + pixelBuffer[i].getG() + pixelBuffer[i].getB())/3;
        pixelBuffer[i].setPixel(gray,
                                gray,
                                gray,
                                pixelBuffer[i].getA());
    }
    //Перекрас серой картинки в цвет
    for (int i = 0; i < Image.getSize(); i++) {

        pixelBuffer[i].setPixel(colorDef(pixelBuffer[i].getR(),r),
                                colorDef(pixelBuffer[i].getG(),g),
                                colorDef(pixelBuffer[i].getB(),b),
                                pixelBuffer[i].getA());
    }
    //Алгоритм применения контрастности
    int palette[256];

    int lAB = 0;

    //Находим яркость всех пикселей
    for (int i = 0; i < Image.getSize(); i++)
    {
        lAB += (int)(pixelBuffer[i].getR() * 0.299 + pixelBuffer[i].getG() * 0.587 + pixelBuffer[i].getB() * 0.114);
    }

    //средняя яркость всех пикселей
    lAB /= Image.getSize();

    //Коэффициент коррекции
    double k = 1.0 + ctr / 100.0;

    //RGB алгоритм изменения контраста
    for (int i = 0; i < 256; i++)
    {
        int delta = (int)i - lAB;
        int temp  = (int)(lAB + k *delta);

        if (temp < 0)
            temp = 0;

        if (temp >= 255)
            temp = 255;
        palette[i] = (unsigned char)temp;
    }

    for (int i = 0; i < Image.getSize(); i++)
    {
        pixelBuffer[i].setPixel((unsigned char)palette[pixelBuffer[i].getR()],
                                (unsigned char)palette[pixelBuffer[i].getG()],
                                (unsigned char)palette[pixelBuffer[i].getB()],
                                pixelBuffer[i].getA());
    }

}
/*!
* Функция для определения нового значения цвета пикселя по старому значению и по заданному пользователем значению
*
* \param c - старое значение цвета пикселя
* \param wc - заданное ползователем значение цвета пикселя
* \return новое значение цвета пикселя
*/
int colorMask::colorDef(int c, int wc){
    if (c>wc){
        return std::max(wc,2*c+wc-256);
    } else {
        return std::min(wc,2*c+wc-256);
    }
}
