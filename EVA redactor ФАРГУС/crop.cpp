#include "crop.h"
/*!
* Функция для ограничения значений до промежутка 0 - 255
* \param value - подаваемое значение
* \return значение в промежутке 0 - 255
*/
int truncate0_255(int value) {
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    else
        return value;
}
/*!
* Функция для ограничения значений до промежутка -100 - 100
* \param value - подаваемое значение
* \return значение в промежутке -100 - 100
*/
int truncate_m100_100(int value) {
    if (value < -100)
        return -100;
    if (value > 100)
        return 100;
    else
        return value;
}
/*!
* Функция для ограничения значений до промежутка 0 - 100
* \param value - подаваемое значение
* \return значение в промежутке 0 - 100
*/
int truncate0_100(int value) {
    if (value < 0)
        return 0;
    if (value > 100)
        return 100;
    else
        return value;
}
