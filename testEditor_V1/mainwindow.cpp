#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);



    zoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    zoomList << 10 << 15 << 22 << 33 << 47 << 68;
    zoomList << 100 << 150 << 220 << 330 << 470 << 680;
    zoomList << 1000 << 1500 << 2200 << 3300 << 4700 << 6800;

}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}




//ИЗОБРАЖЕНИЕ
void MainWindow::on_actionExit_triggered()//EXIT ИЗОБРАЖЕНИЕ
{
    QApplication::quit();
}


void MainWindow::on_actionSave_2_triggered()
{
    if (activeImage) {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение", "C://", "Изображения (*.png *.jpg *.jpeg)");

        if (!fileName.isEmpty()) {
            activeImage->getQImage().save(fileName);
        }
    }
}

void MainWindow::on_actionClose_triggered()//CLOSE ИЗОБРАЖЕНИЕ
{

}
void MainWindow::on_actionOpen_triggered()//OPEN ИЗОБРАЖЕНИЕ
{
    QString imagePath = QFileDialog::getOpenFileName(this,
                                                     tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if(!imagePath.isEmpty()){
        activeImage.reset(new image(imagePath));

        if(activeImage->isValid()){

            qDebug() << activeImage->getFilename();

            scene.clear();
            pixmapItem = scene.addPixmap(QPixmap::fromImage(activeImage->getQImage()));
            scene.setSceneRect(0, 0, activeImage->getW(), activeImage->getH());
            ui->graphicsView->setScene(&scene);

            ui->graphicsView->show();


            ui->statusbar->show();
            ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);


        }
        else {
            activeImage.reset();
            scene.clear();
            ui->graphicsView->hide();
            ui->statusbar->hide();




        }
    }
}
//ИЗОБРАЖЕНИЕ ЗАКОНЧЕНО


//кнопки палитры
void MainWindow::on_pushButton_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();

}
void MainWindow::on_pushButton_2_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_pushButton_4_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_pushButton_5_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_pushButton_6_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_pushButton_7_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
void MainWindow::on_pushButton_8_clicked()
{
    TwoWindow window;
    window.setModal(true);
    window.exec();
}
//кнопки палытры закончены

//кнопки кропа изображения
void MainWindow::zoomUpdate(bool increment)
{
    if(activeImage!= nullptr) {
        double zoom = ui->graphicsView->transform().m11() * 100;

        if (increment) {
            for (double z: zoomList) {
                if ((z - z / 10) > zoom) {
                    zoom = z;
                    break;
                }
            }
        } else {

            for (int i = zoomList.count() - 1; i > 0; i--) {
                double zoomIt = zoomList[i];

                if ((zoomIt + zoomIt / 10) < zoom) {
                    zoom = zoomIt;
                    break;
                }
                qDebug() << "inside zoom out " << zoom;
            }
        }

        ui->graphicsView->setTransform(QTransform::fromScale(zoom / 100, zoom / 100));
    }
}

void MainWindow::on_toolButton_clicked()//уменьшение
{
    if(activeImage!= nullptr) {
        zoomUpdate(false);
        qDebug() << "Zoom out";
    }
}
void MainWindow::on_toolButton_2_clicked()//увеличение
{
    if(activeImage!= nullptr) {
        zoomUpdate(true);
        qDebug() << "Zoom In";
    }
}
//кнопки кропа изображения закончены






//Фильтры
void MainWindow::on_SliderContrast_valueChanged(int value)//констраст
{
    ctr = value;
}


void MainWindow::on_SliderRed_valueChanged(int value)//R
{
    r = value;
}


void MainWindow::on_SliderBlue_valueChanged(int value)//G
{
    b = value;
}


void MainWindow::on_SliderGreen_valueChanged(int value)//B
{
    g = value;
}
void MainWindow::on_ApplyButton_clicked()//применить
{
    if(activeImage!=nullptr){
        colorMask(*activeImage, r, g, b, ctr);
        activeImage->updateArr();
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
    }
}

//Фильбтры закончены








