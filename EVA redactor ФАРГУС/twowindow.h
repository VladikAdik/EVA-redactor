#ifndef TWOWINDOW_H
#define TWOWINDOW_H

#include <QDialog>
#include "pixel.h"

namespace Ui {
class TwoWindow;
}

class TwoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TwoWindow(QWidget *parent = nullptr);
    ~TwoWindow();

private slots:
    void on_horizontalSlider_6_valueChanged(int value);///<слот изменения значения красного ползунка

    void on_horizontalSlider_5_valueChanged(int value);///<слот изменения значения зелёного ползунка

    void on_horizontalSlider_7_valueChanged(int value);///<слот изменения значения синего ползунка

    void on_pushButton_10_clicked();///<слот нажатия на кнопку применения


private:
    int r = 0, g = 0, b = 0;///<переменные значений красного, зелёного и синего спектра изменённого цвета палитры
    Ui::TwoWindow *ui;
};

#endif // TWOWINDOW_H
