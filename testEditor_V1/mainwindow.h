#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QSlider>
#include <QImageWriter>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QList>
#include "image.h"
#include "twowindow.h"
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


    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_actionOpen_triggered();

    void on_actionExit_triggered();





    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_actionClose_triggered();

    void on_actionSave_2_triggered();

    void on_SliderContrast_valueChanged(int value);

    void on_SliderRed_valueChanged(int value);

    void on_SliderGreen_valueChanged(int value);

    void on_SliderBlue_valueChanged(int value);

    void on_ApplyButton_clicked();





private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;
    QGraphicsPixmapItem* pixmapItem;
    std::unique_ptr<image> activeImage;
    QList<double> zoomList;

    int r = 0, g = 0, b = 0, ctr = 0;
protected slots:
    //    void resizeEvent(QResizeEvent *event) override;
    void zoomUpdate(bool increment);


};
#endif // MAINWINDOW_H
