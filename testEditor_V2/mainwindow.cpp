#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    zoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    zoomList << 10 << 15 << 22 << 33 << 47 << 68;
    zoomList << 100 << 150 << 220 << 330 << 470 << 680;
    zoomList << 1000 << 1500 << 2200 << 3300 << 4700 << 6800;

    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);

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

void MainWindow::updatePal(){
    QColor c1 = QColor(palColors[0].getR(), palColors[0].getG(), palColors[0].getB());
    QString s1 = QString("background-color: %1").arg(c1.name());
    ui->pColor1->setStyleSheet(s1);

    QColor c2 = QColor(palColors[1].getR(), palColors[1].getG(), palColors[1].getB());
    QString s2 = QString("background-color: %1").arg(c2.name());
    ui->pColor2->setStyleSheet(s2);

    QColor c3 = QColor(palColors[2].getR(), palColors[2].getG(), palColors[2].getB());
    QString s3 = QString("background-color: %1").arg(c3.name());
    ui->pColor3->setStyleSheet(s3);

    QColor c4 = QColor(palColors[3].getR(), palColors[3].getG(), palColors[3].getB());
    QString s4 = QString("background-color: %1").arg(c4.name());
    ui->pColor4->setStyleSheet(s4);

    QColor c5 = QColor(palColors[4].getR(), palColors[4].getG(), palColors[4].getB());
    QString s5 = QString("background-color: %1").arg(c5.name());
    ui->pColor5->setStyleSheet(s5);

    QColor c6 = QColor(palColors[5].getR(), palColors[5].getG(), palColors[5].getB());
    QString s6 = QString("background-color: %1").arg(c6.name());
    ui->pColor6->setStyleSheet(s6);

    QColor c7 = QColor(palColors[6].getR(), palColors[6].getG(), palColors[6].getB());
    QString s7 = QString("background-color: %1").arg(c7.name());
    ui->pColor7->setStyleSheet(s7);

    QColor c8 = QColor(palColors[7].getR(), palColors[7].getG(), palColors[7].getB());
    QString s8 = QString("background-color: %1").arg(c8.name());
    ui->pColor8->setStyleSheet(s8);
}

void MainWindow::on_actionOpen_triggered()//OPEN ИЗОБРАЖЕНИЕ
{
    QString imagePath = QFileDialog::getOpenFileName(this,
                                                     tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if(!imagePath.isEmpty()){
        activeImage.reset(new image(imagePath));
        previewImage.reset(new image(imagePath));

        if(activeImage->isValid()){

            qDebug() << activeImage->getFilename();

            scene.clear();
            pixmapItem = scene.addPixmap(QPixmap::fromImage(activeImage->getQImage()));
            scene.setSceneRect(0, 0, activeImage->getW(), activeImage->getH());
            ui->graphicsView->setScene(&scene);
            ui->graphicsView->show();

            preview.clear();
            pixmapItemPrev = preview.addPixmap(QPixmap::fromImage(previewImage->getQImage()));
            preview.setSceneRect(0, 0, previewImage->getW(), previewImage->getH());
            ui->graphicsView_3->setScene(&preview);
            ui->graphicsView_3->show();

            ui->statusbar->show();
            ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
            ui->graphicsView_3->fitInView(pixmapItemPrev, Qt::KeepAspectRatio);

            paletteCommand pallete(*activeImage);
            palColors = pallete.getPallete();
            palPriority = pallete.getPalletePriority();
            updatePal();

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

void MainWindow::changeColor(int priority, int r, int g, int b) {
    std::vector<pixel>& pixelArr = previewImage->getPixelArr();
    int dr, dg, db;

    for (int i = 0; i < pixelArr.size(); i++) {
        if (priority == palPriority[i]) {
            dr = palColors[priority].getR() - pixelArr[i].getR();
            dg = palColors[priority].getG() - pixelArr[i].getG();
            db = palColors[priority].getB() - pixelArr[i].getB();
            pixelArr[i].setPixel(r-dr, g-dg, b-db, 255);
        }
    }

    previewImage->updateArr();
    pixmapItemPrev->setPixmap(QPixmap::fromImage(previewImage->getQImage()));
}

//кнопки палитры
void MainWindow::on_pColor1_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c1 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s1 = QString("background-color: %1").arg(c1.name());
    ui->pColor1->setStyleSheet(s1);
    changeColor(0, a/1000000, (a/1000)%1000, a%1000);

}
void MainWindow::on_pColor2_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c2 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s2 = QString("background-color: %1").arg(c2.name());
    ui->pColor2->setStyleSheet(s2);
    changeColor(1, a/1000000, (a/1000)%1000, a%1000);
}

void MainWindow::on_pColor3_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c3 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s3 = QString("background-color: %1").arg(c3.name());
    ui->pColor3->setStyleSheet(s3);
    changeColor(2, a/1000000, (a/1000)%1000, a%1000);
}
void MainWindow::on_pColor4_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c4 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s4 = QString("background-color: %1").arg(c4.name());
    ui->pColor4->setStyleSheet(s4);
    changeColor(3, a/1000000, (a/1000)%1000, a%1000);
}
void MainWindow::on_pColor5_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c5 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s5 = QString("background-color: %1").arg(c5.name());
    ui->pColor5->setStyleSheet(s5);
    changeColor(4, a/1000000, (a/1000)%1000, a%1000);
}
void MainWindow::on_pColor6_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c6 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s6 = QString("background-color: %1").arg(c6.name());
    ui->pColor6->setStyleSheet(s6);
    changeColor(5, a/1000000, (a/1000)%1000, a%1000);
}
void MainWindow::on_pColor7_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c7 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s7 = QString("background-color: %1").arg(c7.name());
    ui->pColor7->setStyleSheet(s7);
    changeColor(6, a/1000000, (a/1000)%1000, a%1000);
}
void MainWindow::on_pColor8_clicked()
{
    TwoWindow window;
    window.setModal(true);
    int a = window.exec();
    QColor c8 = QColor(a/1000000, (a/1000)%1000, a%1000);
    QString s8 = QString("background-color: %1").arg(c8.name());
    ui->pColor8->setStyleSheet(s8);
    changeColor(7, a/1000000, (a/1000)%1000, a%1000);
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


void MainWindow::on_UNDO_clicked()
{
    *previewImage = *activeImage;
    previewImage->updateArr();
    pixmapItemPrev->setPixmap(QPixmap::fromImage(previewImage->getQImage()));
    paletteCommand pallete(*previewImage);
    palColors = pallete.getPallete();
    palPriority = pallete.getPalletePriority();
    updatePal();
}


void MainWindow::on_APPLY_clicked()
{
    *activeImage = *previewImage;
    activeImage->updateArr();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
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
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}


void MainWindow::on_SliderBlue_valueChanged(int value)//G
{
    b = value;
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}


void MainWindow::on_SliderGreen_valueChanged(int value)//B
{
    g = value;
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}
void MainWindow::on_ApplyButton_clicked()//применить
{
    if(activeImage!=nullptr){
        colorMask(*previewImage, r, g, b, ctr);
        previewImage->updateArr();
        pixmapItemPrev->setPixmap(QPixmap::fromImage(previewImage->getQImage()));

        paletteCommand pallete(*previewImage);
        palColors = pallete.getPallete();
        palPriority = pallete.getPalletePriority();
        updatePal();
    }
}

//Фильбтры закончены


