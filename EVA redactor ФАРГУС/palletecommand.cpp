#include "palletecommand.h"
#include <QDebug>
#include <queue>

using namespace std;
/*!
 * \brief Конструктор для палитры
 *
 * Перед определением палитры изображения необходимо сжать изображение до желаемого SIZE.
 * Это нужно сделать, т.к. обработка слишком большого изображения занимает ОЧЕНЬ МНОГО времени
 * и приложение виснет. Далее вызываем функцию определения палитры.
 *
 * \param image - изображение
 */
paletteCommand::paletteCommand(image &image) : picture(image), pixelArr(image.getPixelArr()) {
    int SIZE = 100;
    backupPixelArr = pixelArr;
    backupW = picture.getW();
    backupH = picture.getH();
    if (picture.getW() > SIZE || picture.getH() > SIZE) {

        int x = SIZE, y = SIZE;
        std::vector<pixel> newPixelArr;
        newPixelArr.resize(y*x);

        double x_ratio = picture.getW() / (double) x;
        double y_ratio = picture.getH() / (double) y;
        double px, py;
        for (int i = 0; i < y; i++)
            for (int j = 0; j < x; j++) {
                px = floor(j * x_ratio);
                py = floor(i * y_ratio);
                newPixelArr[i * x + j] = pixelArr[(int) ((py * picture.getW()) + px)];
            }
        picture.setW(x);
        picture.setH(y);
        pixelArr = newPixelArr;
    }

    pallete();
}
/*!
 * \brief Функция определения палитры изображения
 *
 * Основной алгоритм: Median Cut
 *
 * 1. Храним контейнер boxes вместе со значением, обозначающим интервал (подробнее об этом ниже).
 *    В box просто хранится некое динамическое количество пикселей из исходного изображения.
 *
 * 2. Добавляем все пиксели из исходного изображения как первый ящик и используем интервал 0
 *
 * 3. Пока общее количество ящиков меньше нужного количества цветов, продолжаем следующие шаги.
 *
 * 4. Если значение интервала равно 0, то для каждого текущего ящика определяем основной цветовой
 *    канал этого box, а затем сортируем пиксели в этом box по этому цвету. Основной канал — это
 *    тот из Red, Green, Blue и Alpha, который имеет самый широкий интервал. Например, redRange = Max(Red) - Min(Red).
 *    Сортировка просто выполняется сравнением значений каждого пикселя в этом основном канале, все остальные каналы при этом игнорируются.
 *
 * 5. Запоминаем интервал этих основных каналов и сохраняем его вместе с box в контейнере boxes.
 *    Делаем это частично, чтобы не приходилось повторно вычислять уже полученные box.
 *
 * 6. После того, как мы выполним шаги 4 и 5 для каждого box, сортируем контейнер boxes по наибольшему интервалу.\
 *    Это отличается от объяснения в Википедии, потому что мы берём наибольший интервал и подразделяем его,
 *    а не подразделяем ящики, имеющие только небольшой интервал пикселей. Мы всегда подразделяем наибольший ящик,
 *    потому что в нём с наибольшей вероятностью находится слишком много цветов, которые будут представлены одним цветом палитры.
 *
 * 7. Берём самый большой box (большой == с наибольшим интервалом) и удаляем его из контейнера boxes.
 *    Разделяем этот ящик на две равные половины и возвращаем их в контейнер с интервалом 0 (чтобы он заново пересчитался позже).
 *    Не забывайте, что на предыдущем шаге пиксели в нём были упорядочены, поэтому в одной половине находятся большие значения,
 *    а в другой — меньшие. Это позволяет другим цветовым каналам взять верх при повторном вычислении основного канала.
 *
 * Когда мы достигнем количества ящиков, равного нужному количеству цветов, то просто усредняем все пиксели в каждом ящике,
 *
 */
void paletteCommand::pallete() {

    struct boxes {
        int range;
        std::vector<pixel> box;
        int boxSize;
    };

    queue<boxes> list;

    boxes mainBox;
    mainBox.boxSize = picture.getSize();
    mainBox.box.reserve(mainBox.boxSize);
    mainBox.box.resize(mainBox.boxSize);
    mainBox.box = pixelArr;
    list.push(mainBox);

    while (list.size() != N) {
        boxes a1 = list.front();
        list.pop();

        uint8_t maxR, maxG, maxB, minR, minG, minB;
        maxR = minR = a1.box[0].getR();
        maxG = minG = a1.box[0].getG();
        maxB = minB = a1.box[0].getB();

        for (int i = 0; i < a1.boxSize; i++) {
            maxR = max(maxR, a1.box[i].getR());
            minR = min(minR, a1.box[i].getR());
            maxG = max(maxG, a1.box[i].getG());
            minG = min(minG, a1.box[i].getG());
            maxB = max(maxB, a1.box[i].getB());
            minB = min(minB, a1.box[i].getB());
        }

        int redRange = maxR - minR;
        int greenRange = maxG - minG;
        int blueRange = maxB - minB;
        a1.range = max({redRange, greenRange, blueRange});
        int i, j;
        pixel key;
        if (a1.range == redRange) {
            for (i = 1; i < a1.boxSize; i++) {
                key = a1.box[i];
                j = i - 1;
                while (j >= 0 && a1.box[j].getR() > key.getR()) {
                    a1.box[j + 1] = a1.box[j];
                    j = j - 1;
                }
                a1.box[j + 1] = key;
            }
        }
        else if (a1.range == greenRange) {
            for (i = 1; i < a1.boxSize; i++) {
                key = a1.box[i];
                j = i - 1;
                while (j >= 0 && a1.box[j].getG() > key.getG()) {
                    a1.box[j + 1] = a1.box[j];
                    j = j - 1;
                }
                a1.box[j + 1] = key;
            }
        }
        else {
            for (i = 1; i < a1.boxSize; i++) {
                key = a1.box[i];
                j = i - 1;
                while (j >= 0 && a1.box[j].getB() > key.getB()) {
                    a1.box[j + 1] = a1.box[j];
                    j = j - 1;
                }
                a1.box[j + 1] = key;
            }
        }
        a1.range = 0;

        boxes b1, b2;
        b1.boxSize = b2.boxSize = a1.boxSize / 2;
        b1.range = b2.range = 0;
        b1.box.reserve(b1.boxSize);
        b1.box.resize(b1.boxSize);
        b2.box.reserve(b2.boxSize);
        b2.box.resize(b2.boxSize);

        for (int i = 0; i < b1.boxSize; i++) {
            b1.box[i] = a1.box[i];
            b2.box[i] = a1.box[i + b2.boxSize];
        }
        list.push(b1);
        list.push(b2);
    }

    finalP.reserve(N);
    finalP.resize(N);

    for (int i = 0; i < N; i++) {
        int red = 0, green = 0, blue = 0;
        for (int j = 0; j < list.front().boxSize; j++) {
            red += list.front().box[j].getR();
            green += list.front().box[j].getG();
            blue += list.front().box[j].getB();
        }
        red /= list.front().boxSize;
        green /= list.front().boxSize;
        blue /= list.front().boxSize;
        finalP[i].setPixel(red, green, blue, 255);
        list.pop();
    }

    pixelArr = backupPixelArr;
    picture.setW(backupW);
    picture.setH(backupH);
    qDebug() << "Pallate was created";
}
/*!
 * Функция для получения палитры
 */

std::vector<pixel> paletteCommand::getPallete() {
    return finalP;
}
/*!
 * \brief Функция для присвоения каждому пикселю самый подходящий цвет в палитре.
 *
 * Сначала для пикселя определяем самое минимальное евклидово растояние между цветом
 * пикселя и цветами палитры, это будет самый подходящий цвет палитры.
 *
 * Далее определяем какому цвету палитры принадлежит минимальное растояние и
 * присваеваем пикселю самый подходящий цвет палитры.
 *
 * Повторяем со всеми пикселями в изображении.
 *
 * \return Массив приоритетов для каждого пикселя
 */
std::vector<int> paletteCommand::getPalletePriority() {
    std::vector<pixel> colors;
    colors.reserve(picture.getSize());
    colors.resize(picture.getSize());

    colors = pixelArr;

    vector<int> priority;
    priority.reserve(picture.getSize());
    priority.resize(picture.getSize());

    for (int i = 0; i < picture.getSize(); i++){
        int minDistance = 999;
        for (int j = 0; j < finalP.size(); j++) {
            int redD = colors[i].getR() - finalP[j].getR();
            int greenD = colors[i].getG() - finalP[j].getG();
            int blueD = colors[i].getB() - finalP[j].getB();
            int totalD = sqrt((redD*redD) + (greenD*greenD) + (blueD*blueD));

            minDistance = min(minDistance, totalD);
        }
        bool found = false;
        int count = 0;

        while (found == false && count < N) {
            int redD = colors[i].getR() - finalP[count].getR();
            int greenD = colors[i].getG() - finalP[count].getG();
            int blueD = colors[i].getB() - finalP[count].getB();
            int totalD = sqrt((redD*redD) + (greenD*greenD) + (blueD*blueD));
            if (totalD == minDistance) {
                priority[i] = count;
                found = true;
            }
            count++;
        }
    }

    qDebug() << "PalletePriority was created";
    return priority;
}
