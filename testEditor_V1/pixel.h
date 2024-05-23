#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>


class pixel {

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    pixel();
    pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    pixel(const pixel &pixel);

    bool operator==(const pixel &pixel) const;
    bool operator!=(const pixel &pixel) const;

    uint8_t getR() const;
    uint8_t getG() const;
    uint8_t getB() const;
    uint8_t getA() const;

    void setPixel(int r, int g, int b, int a);

    static QColor toQColor(const pixel &);
    static pixel fromQColor(const QColor &);
};

#endif // PIXEL_H
