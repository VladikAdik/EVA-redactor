#include "inputdialog.h"

#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDebug>

/*!
* \brief Конструктор класса InputDialog - диалоговое окно с несколькими полями ввода
*
* Создаётся класс компоновки QFormLayout. Проходясь по массиву названий полей ввода создаётся ряд из поля ввода и его названия и добавляем на форму. Создаются кнопки "принять" и "отклонить"
* \param QList<QString>& fields массив названий полей ввода
* \param min - минимальное значение полей ввода
* \param max - максимальное значение полей ввода
* \param step - шаг изменения значений в полях ввода
* \param *parent - родительское окно, на которое будут подаваться полученные в диалоговом окне значения
*/
InputDialog::InputDialog(const QList<QString>& fields, int min, int max, int step, QWidget *parent) : QDialog(parent),
    fields(fields), min(min), max(max), step(step)
{
    setWindowTitle("Change size");
    QFormLayout* layout = new QFormLayout(this);

    for(const auto &field : fields){

        QLabel* label = new QLabel(field, this);
        QSpinBox* edit = new QSpinBox(this);
        edit->setMinimum(min);
        edit->setMaximum(max);
        edit->setSingleStep(step);
        edit->setValue(0);
        layout->addRow(label, edit);
        values << edit;
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                                       Qt::Horizontal, this);

    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted,
            this, &InputDialog::accept);

    connect(buttonBox, &QDialogButtonBox::rejected,
            this, &InputDialog::reject);

    setLayout(layout);
}
/*!
* \brief Функция получения значений из диалогового окна
*
* Создаётся список для получаемых значений. Для каждого поля ввода создаётся отдельный диалог и из него записывается значение в созданный список. При получении всех значений список возвращается в родительское окно
* \param *parent - родительское окно, на которое будут подаваться полученные в диалоговом окне значения
* \param QList<QString>& fields массив названий полей ввода
* \param min - минимальное значение полей ввода
* \param max - максимальное значение полей ввода
* \param step - шаг изменения значений в полях ввода
* \param ok - переменная, определяющая, если пользователь нажал на кнопку "применить"
* \return список значений из диалогового окна
*/
QList<int> InputDialog::getFields(QWidget *parent, QList<QString> fields, int min, int max, int step, bool *ok)
{
    InputDialog* dialog = new InputDialog(fields, min, max, step, parent);

    QList<int> list;

    bool okInput = dialog->exec();

    if(okInput){
        *ok = okInput;
        foreach(auto value, dialog->values){
            list << value->value();
        }
    }

    dialog->deleteLater();
    return list;
}
