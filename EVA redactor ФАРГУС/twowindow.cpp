#include "twowindow.h"
#include "ui_twowindow.h"

/*!
* \brief Конструктор класса
*
* Создаётся прямоугольник чёрного цвета, отображающий заданный пользователем цвет
* \param parent - родительское окно
*/
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
/*!
* \brief Изменение значения ползунка красного цвета
*
* Изменяется значение красного спектра. Обновляется прямоугольник, обозначающий пользовательский цвет.
* \param value - новое значение ползунка
*/
void TwoWindow::on_horizontalSlider_6_valueChanged(int value)//R
{
    r = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}

/*!
* \brief Изменение значения ползунка зелёного цвета
*
* Изменяется значение зелёного спектра. Обновляется прямоугольник, обозначающий пользовательский цвет.
* \param value - новое значение ползунка
*/
void TwoWindow::on_horizontalSlider_5_valueChanged(int value)//G
{
    g = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}

/*!
* \brief Изменение значения ползунка синего цвета
*
* Изменяется значение синего спектра. Обновляется прямоугольник, обозначающий пользовательский цвет.
* \param value - новое значение ползунка
*/
void TwoWindow::on_horizontalSlider_7_valueChanged(int value)//B
{
    b = value;
    QColor color = QColor(r, g, b);
    QString s1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(s1);
}
/*!
* \brief кнопка применить
*
* заданный пользователем цвет передаётся в родительское окно, обновляя цвет палитры
*/
void TwoWindow::on_pushButton_10_clicked()//применить
{
    int kok = (r * 1000 + g) * 1000 + b;
    done(kok);
}

