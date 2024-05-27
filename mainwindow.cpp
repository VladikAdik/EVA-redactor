#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    QString fileName = QFileDialog::getOpenFileName(this, "Выберите изображение", "C://", "Изображения (*.png *.jpg *.jpeg)");

    if (!fileName.isEmpty()) {
        activeImage.reset(new image(fileName));

        if (activeImage->isValid()) {
            scene.clear();
            pixmapItem = scene.addPixmap(QPixmap::fromImage(activeImage->getQImage()));
            scene.setSceneRect(0, 0, activeImage->getW(), activeImage->getH());
            ui->graphicsView->setScene(&scene);

            ui->graphicsView->show();


        }


    }

}


void MainWindow::on_cMaskButton_clicked()
{
    if(activeImage!=nullptr){
        colorMask(*activeImage, r, g, b, ctr);
            //commandManager.execute(c);
        activeImage->updateArr();
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    }
}


void MainWindow::on_SliderRed_valueChanged(int value)
{
    r = value;
}
void MainWindow::on_SliderGreen_valueChanged(int value)
{
    g = value;
}
void MainWindow::on_SliderBlue_valueChanged(int value)
{
    b = value;
}
void MainWindow::on_SliderContrast_valueChanged(int value)
{
    ctr = value;
}
