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
#include "palletecommand.h"

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

    void on_actionClose_triggered();

    void on_actionSave_2_triggered();

    void on_SliderContrast_valueChanged(int value);

    void on_SliderRed_valueChanged(int value);

    void on_SliderGreen_valueChanged(int value);

    void on_SliderBlue_valueChanged(int value);

    void on_ApplyButton_clicked();


    void on_UNDO_clicked();

    void on_APPLY_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;
    QGraphicsScene preview;
    QGraphicsPixmapItem* pixmapItem;
    QGraphicsPixmapItem* pixmapItemPrev;
    std::unique_ptr<image> activeImage;
    std::unique_ptr<image> previewImage;
    std::vector<pixel> palColors;
    std::vector<int> palPriority;
    QList<double> zoomList;


    void updatePal();
    void changeColor(int priority, int r, int g, int b);

    int r = 0, g = 0, b = 0, ctr = 0;
protected slots:
    //    void resizeEvent(QResizeEvent *event) override;
    void zoomUpdate(bool increment);


};
#endif // MAINWINDOW_H
