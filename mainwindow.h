#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QSlider>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include "image.h"
#include "colormask.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_cMaskButton_clicked();

    void on_SliderRed_valueChanged(int value);
    void on_SliderGreen_valueChanged(int value);
    void on_SliderBlue_valueChanged(int value);
    void on_SliderContrast_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;
    QGraphicsPixmapItem* pixmapItem;
    std::unique_ptr<image> activeImage;

    int r = 0, g = 0, b = 0, ctr = 0;



};
#endif // MAINWINDOW_H
