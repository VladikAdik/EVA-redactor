#ifndef MULTIPLEINPUTDIALOG_H
#define MULTIPLEINPUTDIALOG_H

#include <QSpinBox>
#include <QDialog>

class QLabel;

class InputDialog : public QDialog
{
    Q_OBJECT
public:

    static QList<int> getFields(QWidget *parent, QList<QString> fields, int min, int max, int step, bool *ok);///<получение значений из полей ввода

private:
    explicit InputDialog(const QList<QString>& fields, int min=0, int max=100, int step=1, QWidget *parent = nullptr);///<конструктор диалога ввода
    QList<QSpinBox* > values;///<поля ввода
    QList<QString> fields;///<названия полей ввода
    int min;///<минимальное значение полей ввода
    int max;///<максимальное значение полей ввода
    int step;///<шаг изменения значений полей ввода
};

#endif // MULTIPLEINPUTDIALOG_H
