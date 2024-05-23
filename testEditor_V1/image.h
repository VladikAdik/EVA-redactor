#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFileInfo>
#include "pixel.h"
#include <vector>

class image {

private:
    QImage rawImage;
    QString path;
    QString imageName;
    std::vector<pixel> pixelArr;
    int w;
    int h;
    bool isImageValid;

public:
    image(QString &path);

    void createPixelArr();

    QString getPath() const;
    QString getFilename() const;
    std::vector<pixel>& getPixelArr();
    int getW() const;
    int getH() const;
    size_t getSize() const;
    QImage& getQImage();
    bool isValid() const;

    void setW(int w);
    void setH(int h);
    void setPath(QString path);

    void updateArr();
};

#endif // IMAGE_H
