#include "pixel.h"
#include "crop.h"

/*!
 * \brief Конструктор класса pixel.
 * \param r - значение красного оттенка желаемого цвета
 * \param g - значение зелёного оттенка желаемого цвета
 * \param b - значение синего оттенка желаемого цвета
 * \param a - значение альфа канала желаемого цвета
 */
pixel::pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

/*!
 * \brief Конструктор класса pixel.
 * По-умолчанию создается черный пиксель
 */
pixel::pixel() : pixel(0, 0, 0, 255) {}


/*!
 * \brief Конструктор класса pixel.
 * \param color - пиксель с каким-либо установленным цветом
 */
pixel::pixel(const pixel &color) {
    this->r = color.getR();
    this->g = color.getG();
    this->b = color.getB();
    this->a = color.getA();
}

/*!
 * Оператор проверки равенства пикселей .
 * \param pixel - сравниваемый пиксель
 * \return 1 - если цвета сходятся, 0 - если нет
 */
bool pixel::operator==(const pixel &pixel) const {
    if (getR() == pixel.getR() &&
        getG() == pixel.getG() &&
        getB() == pixel.getB() &&
        getA() == pixel.getA())
        return true;
    else
        return false;
}

/*!
 * Оператор проверки неравенства пикселей .
 * \param pixel - сравниваемый пиксель
 * \return 0 - если цвета сходятся, 1 - если нет
 */
bool pixel::operator!=(const pixel &pixel) const {
    return !operator==(pixel);
}

/*!
 * Функция получения значение красного оттенка цвета.
 * \return r - значение красного оттенка
 */
uint8_t pixel::getR() const { return r; }

/*!
 * Функция получения значение зеленого оттенка цвета.
 * \return g - значение зеленого оттенка
 */
uint8_t pixel::getG() const { return g; }

/*!
 * Функция получения значение синего оттенка цвета.
 * \return b - значение синего оттенка
 */
uint8_t pixel::getB() const { return b; }

/*!
 * Функция получения значение альфа канала цвета.
 * \return a - значение альфа канала цвета
 */
uint8_t pixel::getA() const { return a; }

/*!
 * Функция задачи цвета пикселя.
 * \param r - значение красного оттенка желаемого цвета
 * \param g - значение зелёного оттенка желаемого цвета
 * \param b - значение синего оттенка желаемого цвета
 * \param a - значение альфа канала желаемого цвета
 */
void pixel::setPixel(int r, int g, int b, int a) {
    this->r = truncate0_255(r);
    this->g = truncate0_255(g);
    this->b = truncate0_255(b);
    this->a = truncate0_255(a);
}

/*!
 * Функция преобразования из pixel в QColor.
 * \param oldc - изначальная переманная типа pixel
 * \return newc - получившаяся переманная типа QColor
 */
QColor pixel::toQColor(const pixel &oldc) {
    QColor newc(oldc.getR(), oldc.getG(), oldc.getB(), oldc.getA());
    return newc;
}

/*!
 * Функция преобразования из QColor в pixel.
 * \param oldc - изначальная переманная типа QColor
 * \return pixel - получившаяся переманная типа pixel
 */
pixel pixel::fromQColor(const QColor &oldc) {
    int rc;
    int gc;
    int bc;
    int ac;

    oldc.getRgb(&rc, &gc, &bc, &ac);

    return pixel(rc, gc, bc, ac);
}
