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
    void on_horizontalSlider_6_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);

    void on_pushButton_10_clicked();


private:
    int r = 0, g = 0, b = 0;
    Ui::TwoWindow *ui;
};

#endif // TWOWINDOW_H
