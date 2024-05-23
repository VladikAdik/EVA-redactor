#ifndef PALLETECOMMAND_H
#define PALLETECOMMAND_H

#include "image.h"

class paletteCommand {

private:
    int N = 8;
    image &picture;
    std::vector<pixel>& pixelArr;
    std::vector<pixel> finalP;

    std::vector<pixel> backupPixelArr;
    int backupW;
    int backupH;

    void pallete();

public:
    paletteCommand(image &image);

    std::vector<pixel> getPallete();

    std::vector<int> getPalletePriority();

};
#endif // PALLETECOMMAND_H
