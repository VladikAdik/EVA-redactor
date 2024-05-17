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

