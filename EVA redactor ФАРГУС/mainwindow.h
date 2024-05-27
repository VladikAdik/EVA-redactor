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
#include "inputdialog.h"
#include "colormask.h"
#include "palletecommand.h"
#include <QCloseEvent>
#include <QSharedPointer>



QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionOpen_triggered();

    void on_actionExit_triggered();


    void on_pColor1_clicked();

    void on_pColor2_clicked();

    void on_pColor3_clicked();

    void on_pColor4_clicked();

    void on_pColor5_clicked();

    void on_pColor6_clicked();

    void on_pColor7_clicked();

    void on_pColor8_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();



    void on_actionSave_2_triggered();

    void on_SliderContrast_valueChanged(int value);

    void on_SliderRed_valueChanged(int value);

    void on_SliderGreen_valueChanged(int value);

    void on_SliderBlue_valueChanged(int value);

    void on_ApplyButton_clicked();


    void on_UNDO_clicked();

    void on_APPLY_clicked();
    void on_actionZoom_Adapt_triggered();

    void on_actionImage_size_triggered();
    void on_actionZoom_Adapt_triggered2();



    void on_actionScene_size_triggered();



private:
    Ui::MainWindow *ui;///<Графическое окно
    QGraphicsScene scene;///<Главное окно изображения
    QGraphicsScene preview;///<Предварительное окно изображения
    QGraphicsPixmapItem* pixmapItem;///<Растровое изображение для отображения в главном окне
    QGraphicsPixmapItem* pixmapItemPrev;///<Растровое изображение для отображения в предварительном окне
    std::unique_ptr<image> activeImage;///<Основное изображение
    std::unique_ptr<image> previewImage;///<Предварительное изображение
    std::vector<pixel> palColors;///<Цвета в палитре
    std::vector<int> palPriority;///<
    QList<double> zoomList;///<Определенная кратность изображения


    int xi = 0,yi = 0;




    void updatePal();///<функция обновления палитры
    void changeColor(int priority, int r, int g, int b);///<функция изменения всех пикселей определённого цвета палитры


    int r = 0, g = 0, b = 0, ctr = 0;///<переменные значений красного, зелёного и синего спектров и контраста для желаемого цветового фильтра изображения
protected slots:
    void zoomUpdate(bool increment);


};
#endif // MAINWINDOW_H
