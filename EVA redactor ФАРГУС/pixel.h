#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>


class pixel {

private:
    uint8_t r;///<значение красного спектра пикселя
    uint8_t g;///<значение зелёного спектра пикселя
    uint8_t b;///<значение синего спектра пикселя
    uint8_t a;///<значение альфа спектра пикселя (прозрачность)

public:
    pixel();///<конструктор
    pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);///<конструктор
    pixel(const pixel &pixel);///<конструктор

    bool operator==(const pixel &pixel) const;///<оператор проверки равенства пикселей
    bool operator!=(const pixel &pixel) const;///<оператор проверки неравенства пикселей

    uint8_t getR() const;///<функция получения красного спектра пикселя
    uint8_t getG() const;///<функция получения зелёного спектра пикселя
    uint8_t getB() const;///<функция получения синего спектра пикселя
    uint8_t getA() const;///<функция получения альфа спектра пикселя

    void setPixel(int r, int g, int b, int a);///<функция задачи значения пикселя

    static QColor toQColor(const pixel &);///<функция преобразования переменной типа QColor в pixel
    static pixel fromQColor(const QColor &);///<функция преобразования переменной типа pixel в QColor
};

#endif // PIXEL_H
