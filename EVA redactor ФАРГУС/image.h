#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFileInfo>
#include "pixel.h"
#include <vector>

class image {

private:
    QImage rawImage;///<изображение в формате QImage
    QString path;///<путь до изображения
    QString imageName;///<имя изображения
    std::vector<pixel> pixelArr;///<изображение в формате массива пикселей
    int w;///<ширина изображения
    int h;///<высота изображения
    bool isImageValid;///<проверка корректности загруженного изображения

public:
    image(QString &path);///<конструктор класса

    void createPixelArr();///<создание массива пикселей
    QString getPath() const;///<функция получения переменной пути
    QString getFilename() const;///<функция получения переменной имени файла
    std::vector<pixel>& getPixelArr();///<функция получения массива пикселей
    int getW() const;///<функция получения переменной ширины
    int getH() const;///<функция получения переменной длины
    size_t getSize() const;///<функция получения размера изображения
    QImage& getQImage();///<функция получения изображения в формате QImage
    bool isValid() const;///<функция проверки корректности загруженного изображения

    void setW(int w);///<функция изменения переменной ширины
    void setH(int h);///<функция изменения переменной высоты
    void setPath(QString path);///<функция изменения переменной пути

    void updateArr();///<функция обновления изображения QImage по изменённому массиву

};

#endif // IMAGE_H
