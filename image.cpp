#include "image.h"

image::image(QString &path) : rawImage(path), path(path), isImageValid(true) {
    if(rawImage.isNull()){
        isImageValid = false;
    }

    rawImage = rawImage.convertToFormat(QImage::Format_ARGB32);
    w = rawImage.width();
    h = rawImage.height();

    pixelArr.reserve(getSize());
    createPixelArr();
    QFileInfo qFilename(path);
    imageName = qFilename.fileName();
}

void image::createPixelArr() {
    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
            pixelArr.emplace_back(pixel::fromQColor(rawImage.pixelColor(x, y)));
        }
}

QString image::getPath() const {
    return path;
}

QString image::getFilename() const {
    return imageName;
}

std::vector<pixel>& image::getPixelArr() {
    return pixelArr;
}

int image::getW() const {
    return w;
}

int image::getH() const {
    return h;
}

size_t image::getSize() const {
    return w * h;
}

QImage& image::getQImage() {
    return rawImage;
}

bool image::isValid() const {
    return isImageValid;
}

void image::setW(int w) {
    this->w = w;
}

void image::setH(int h) {
    this->h = h;
}

void image::setPath(QString path) {
    this->path = path;
}

void image::updateArr(){
    rawImage = QImage(w, h, QImage::Format_ARGB32);

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            rawImage.setPixelColor(x, y, pixel::toQColor(pixelArr[y * w + x]));
        }
}
