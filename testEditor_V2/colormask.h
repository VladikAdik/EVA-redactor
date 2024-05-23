#ifndef COLORMASK_H
#define COLORMASK_H

#include "image.h"

class colorMask
{
private:
    image &Image;
    std::vector<pixel>& pixelBuffer;
    std::vector<pixel> backupPixelBuffer;
    int r, g, b, ctr;

    void colorMaskExec();
    int colorDef(int c, int wc);
public:
    colorMask(image &Image, int r, int g, int b, int ctr);
};

#endif // COLORMASK_H
