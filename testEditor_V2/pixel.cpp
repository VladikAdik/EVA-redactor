#include "pixel.h"
#include "crop.h"

pixel::pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

pixel::pixel() : pixel(0, 0, 0, 255) {}

pixel::pixel(const pixel &color) {
    this->r = color.getR();
    this->g = color.getG();
    this->b = color.getB();
    this->a = color.getA();
}

bool pixel::operator==(const pixel &pixel) const {
    if (getR() == pixel.getR() &&
        getG() == pixel.getG() &&
        getB() == pixel.getB() &&
        getA() == pixel.getA())
        return true;
    else
        return false;
}

bool pixel::operator!=(const pixel &pixel) const {
    return !operator==(pixel);
}

uint8_t pixel::getR() const { return r; }

uint8_t pixel::getG() const { return g; }

uint8_t pixel::getB() const { return b; }

uint8_t pixel::getA() const { return a; }

void pixel::setPixel(int r, int g, int b, int a) {
    this->r = truncate0_255(r);
    this->g = truncate0_255(g);
    this->b = truncate0_255(b);
    this->a = truncate0_255(a);
}

QColor pixel::toQColor(const pixel &oldc) {
    QColor newc(oldc.getR(), oldc.getG(), oldc.getB(), oldc.getA());
    return newc;
}

pixel pixel::fromQColor(const QColor &oldc) {
    int rc;
    int gc;
    int bc;
    int ac;

    oldc.getRgb(&rc, &gc, &bc, &ac);

    return pixel(rc, gc, bc, ac);
}
