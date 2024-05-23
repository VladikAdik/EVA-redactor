#include "twowindow.h"
#include "ui_twowindow.h"

TwoWindow::TwoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TwoWindow)
{
    ui->setupUi(this);
}

TwoWindow::~TwoWindow()
{
    delete ui;
}

void TwoWindow::on_horizontalSlider_6_valueChanged(int value)//R
{

}


void TwoWindow::on_horizontalSlider_5_valueChanged(int value)//G
{

}


void TwoWindow::on_horizontalSlider_7_valueChanged(int value)//B
{

}

void TwoWindow::on_pushButton_10_clicked()//применить
{

}

