#include "image.h"
/*!
* \brief Конструктор для класса image
*
* Изображение конвертируется в 32-битный формат, определяется высота и ширина, задаётся массив пикселей с помощью функции CreatePixelArr(), задаётся имя файла и путь до него.
* \param path - путь к изображению
*/
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
/*!
* Функция создания массива пикселей по изображению QImage
*/
void image::createPixelArr() {
    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
            pixelArr.emplace_back(pixel::fromQColor(rawImage.pixelColor(x, y)));
        }
}

/*!
* Функция получения пути
* \return путь
*/
QString image::getPath() const {
    return path;
}
/*!
* Функция получения названия файла
* \return имя файла
*/
QString image::getFilename() const {
    return imageName;
}
/*!
* Функция получения массива пикселей
* \return массив пикселей
*/
std::vector<pixel>& image::getPixelArr() {
    return pixelArr;
}
/*!
* Функция получения ширины
* \return ширина изображения
*/
int image::getW() const {
    return w;
}
/*!
* Функция получения высоты
* \return высота изображения
*/
int image::getH() const {
    return h;
}
/*!
* Функция получения размера изображения
* \return размер изображения
*/
size_t image::getSize() const {
    return w * h;
}
/*!
* Функция получения изображения формата QImage
* \return изображение в формате QImage
*/
QImage& image::getQImage() {
    return rawImage;
}
/*!
* Функция проверки корректности загруженного изображения
* \return корректность изображения
*/
bool image::isValid() const {
    return isImageValid;
}
/*!
* функция установления значения ширины
* \param w - ширина
*/
void image::setW(int w) {
    this->w = w;
}
/*!
* функция установления значения высоты
* \param h - высота
*/
void image::setH(int h) {
    this->h = h;
}
/*!
* функция установления пути
* \param path - путь
*/
void image::setPath(QString path) {
    this->path = path;
}
/*!
* функция построения изображения по массиву
*/
void image::updateArr(){
    rawImage = QImage(w, h, QImage::Format_ARGB32);

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            rawImage.setPixelColor(x, y, pixel::toQColor(pixelArr[y * w + x]));
        }
}

