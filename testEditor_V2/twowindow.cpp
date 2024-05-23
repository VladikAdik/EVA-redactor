#include "twowindow.h"
#include "ui_twowindow.h"


TwoWindow::TwoWindow(QWidget *parent) : QDialog(parent) , ui(new Ui::TwoWindow) {
    ui->setupUi(this);
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}

TwoWindow::~TwoWindow()
{
    delete ui;
}

void TwoWindow::on_horizontalSlider_6_valueChanged(int value)//R
{
    r = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}


void TwoWindow::on_horizontalSlider_5_valueChanged(int value)//G
{
    g = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}


void TwoWindow::on_horizontalSlider_7_valueChanged(int value)//B
{
    b = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}

void TwoWindow::on_pushButton_10_clicked()//применить
{
    int kok = (r * 1000 + g) * 1000 + b;
    done(kok);
}

