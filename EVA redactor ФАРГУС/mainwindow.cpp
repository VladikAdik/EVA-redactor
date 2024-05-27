#include "mainwindow.h"
#include "ui_mainwindow.h"



/*!
  \brief Конструктор для класса MainWindow
 *
 * Инициализирует главное окно с определенными настройками и отключает определенные элементы пользовательского интерфейса.
 *
 * \param parent Указатель на родительский виджет
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    zoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    zoomList << 10 << 15 << 22 << 33 << 47 << 68;
    zoomList << 100 << 150 << 220 << 330 << 470 << 680;
    zoomList << 1000 << 1500 << 2200 << 3300 << 4700 << 6800;

    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);

    ui->toolButton->setEnabled(false);
    ui->toolButton_2->setEnabled(false);

    ui->pColor1->setEnabled(false);
    ui->pColor2->setEnabled(false);
    ui->pColor3->setEnabled(false);
    ui->pColor4->setEnabled(false);
    ui->pColor5->setEnabled(false);
    ui->pColor6->setEnabled(false);
    ui->pColor7->setEnabled(false);
    ui->pColor8->setEnabled(false);

    ui->SliderContrast->setEnabled(false);
    ui->SliderRed->setEnabled(false);
    ui->SliderGreen->setEnabled(false);
    ui->SliderBlue->setEnabled(false);
    ui->ApplyButton->setEnabled(false);

    ui->UNDO->setEnabled(false);
    ui->APPLY->setEnabled(false);
    ui->actionImage_size->setEnabled(false);
    ui->actionSave_2->setEnabled(true);


}

MainWindow::~MainWindow() {
    delete ui;
}

/*!
 * \brief MainWindow::on_actionExit_triggered()- Выход из программы при нажатии кнопки
 */
//ИЗОБРАЖЕНИЕ
void MainWindow::on_actionExit_triggered()//EXIT ИЗОБРАЖЕНИЕ
{
    QApplication::quit();
}

/*!
 * \brief MainWindow::on_actionSave_2_triggered - Слот для сохранения изображения, запускаемого нажатием на определенное действие
 *
 * Если activeImage существует, пользователю предлагается выбрать путь к файлу для сохранения изображения в формате PNG, JPG или JPEG.
 *
 * \note Если имя файла не пустое, QImage activeImage сохраняется по выбранному пути к файлу.
 *
 */
void MainWindow::on_actionSave_2_triggered()
{
    if (activeImage) {
        QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение", "C://", "Изображения (*.png *.jpg *.jpeg)");

        if (!fileName.isEmpty()) {
            activeImage->getQImage().save(fileName);
        }
    }
}



/*!
* \brief MainWindow::updatePal Обновляет цвета палитры в пользовательском интерфейсе главного окна

* Эта функция обновляет цвета фона элементов палитры в пользовательском интерфейсе главного окна.
* Она извлекает значения RGB для каждого цвета палитры из массива, создает объект QColor с этими значениями,
*создает строку стиля CSS с цветом фона, равным соответствующему QColor, и применяет этот стиль к каждому элементу палитры.

* Эта функция предполагает наличие следующих переменных-членов:
* - palColors: массив, содержащий значения RGB цветов палитры
* - ui: указатель на элементы пользовательского интерфейса главного окна
*/
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



/*!
*        \brief MainWindow::on_actionOpen_triggered() - Открывает файл изображения, выбранный пользователем
*
*    Эта функция запускается, когда пользователь выбирает действие "Открыть" в приложении.
*    Программа открывает диалоговое окно, в котором пользователь может выбрать файл изображения (.png, .jpg, .bmp), загружает изображение,
*    отображает его в основном графическом режиме, создает предварительный просмотр изображения и выполняет несколько обновлений пользовательского интерфейса.
*
*       \details
*       1. Открывает диалоговое окно с файлом, в котором пользователь может выбрать файл изображения
*        2. Создает объекты activeImage и previewImage с выбранным файлом изображения
*        3. Если activeImage является допустимым:
*        - Отображает изображение activeImage в основном графическом режиме
*         - Создает предварительный просмотр изображения и отображает его в отдельном графическом режиме
*         - Отображает строку состояния и сопоставляет изображения в графических режимах
*         - Извлекает палитру изображений и обновляет пользовательский интерфейс с помощью цветов палитры
*         - Включает различные элементы пользовательского интерфейса для взаимодействия с изображением
*        4. Если параметр activeImage недействителен, сбросьте значение activeImage, очистите сцену, скройте основной графический вид
*        и строку состояния.
*
*
*/
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

            ui->toolButton->setEnabled(true);
            ui->toolButton_2->setEnabled(true);

            ui->pColor1->setEnabled(true);
            ui->pColor2->setEnabled(true);
            ui->pColor3->setEnabled(true);
            ui->pColor4->setEnabled(true);
            ui->pColor5->setEnabled(true);
            ui->pColor6->setEnabled(true);
            ui->pColor7->setEnabled(true);
            ui->pColor8->setEnabled(true);

            ui->SliderContrast->setEnabled(true);
            ui->SliderRed->setEnabled(true);
            ui->SliderGreen->setEnabled(true);
            ui->SliderBlue->setEnabled(true);
            ui->ApplyButton->setEnabled(true);

            ui->UNDO->setEnabled(true);
            ui->APPLY->setEnabled(true);
            ui->actionImage_size->setEnabled(true);
             ui->actionSave_2->setEnabled(true);


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
/*!
* \brief Изменяет цвет пикселей на изображении в зависимости от приоритета
*
* Эта функция принимает уровень приоритета и значения цвета RGB в качестве параметров и изменяет цвет
* пикселей на изображении с указанным уровнем приоритета путем настройки их значений RGB. Он
* обновляет массив пикселей, а затем обновляет изображение предварительного просмотра, отображаемое в приложении.
*
* \param priority целое число, представляющее уровень приоритета
* \param r целое значение для красного компонента нового цвета
* \param g - целое значение для зеленого компонента нового цвета
* \param b - целое значение для синего компонента нового цвета
*/
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
/*!
 * Для всех on_pColor_clicked()
 * \brief Обработчик нажатия кнопки палитры
 *
 * При нажатии на кнопку палитры создается объект окна TwoWindow и устанавливается модальный режим.
 * Затем происходит выполнение диалогового окна, и возвращаемое значение сохраняется в переменной a.
 * Создается объект QColor c1 с использованием различных операций для получения значения RGB из переменной a.
 * Создается строка s1 с CSS стилем "background-color" и цветом, полученным от объекта c1.
 * Затем устанавливается стиль кнопки pColor1 с помощью созданной строки s1.
 * Вызывается функция changeColor для изменения цвета элемента с индексом 0 на цвет, полученный из переменной a.
 */
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
/*!
    \brief описание главного окна::zoomUpdate Обновляет уровень масштабирования активного изображения в графическом представлении
    \param ncrement Flag, увеличивать уровень масштабирования (true) или уменьшать (false).

    Эта функция обновляет уровень масштабирования активного изображения, отображаемого в графическом режиме, на основе флажка "Увеличить".
    Если значение "увеличить" равно true, оно увеличивает уровень масштабирования. Если значение "ложно", оно уменьшает уровень масштабирования.

    Уровень масштабирования получается из текущей матрицы преобразования графического представления и умножается на 100.

    \param zoomList Список уровней масштабирования, доступных для графического представления

*/
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

/*!
 * \brief Обработчик нажатия кнопки UNDO.
 *
 * Восстанавливает предыдущее состояние изображения.
 * Обновляет предварительное изображение, устанавливает его в элемент QGraphicsPixmapItem,
 * обновляет палитру и вызывает функцию масштабирования изображения.
 */
void MainWindow::on_UNDO_clicked()
{
    *previewImage = *activeImage;
    previewImage->updateArr();
    pixmapItemPrev->setPixmap(QPixmap::fromImage(previewImage->getQImage()));
    paletteCommand pallete(*previewImage);
    palColors = pallete.getPallete();
    palPriority = pallete.getPalletePriority();
    updatePal();
    on_actionZoom_Adapt_triggered();

}

/*!
 * \brief Обработчик нажатия кнопки APPLY.
 *
 * Применяет изменения к активному изображению.
 * Обновляет активное изображение, устанавливает его в элемент QGraphicsPixmapItem
 * и вызывает функции масштабирования изображения.
 */
void MainWindow::on_APPLY_clicked()
{
    *activeImage = *previewImage;
    activeImage->updateArr();
    pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));


    on_actionZoom_Adapt_triggered();
    on_actionZoom_Adapt_triggered2();
}
/*!
 * \brief Обработчик нажатия на кнопку уменьшения.
 *
 * Если активное изображение не равно nullptr, вызывается функция zoomUpdate для уменьшения изображения.
 * Также выводится сообщение "Zoom out" в консоль.
 */
void MainWindow::on_toolButton_clicked()//уменьшение
{
    if(activeImage!= nullptr) {
        zoomUpdate(false);
        qDebug() << "Zoom out";
    }
}

/*!
 * \brief Обработчик нажатия на кнопку увеличения.
 *
 * Если активное изображение не равно nullptr, вызывается функция zoomUpdate для увеличения изображения.
 * Также выводится сообщение "Zoom In" в консоль.
 */
void MainWindow::on_toolButton_2_clicked()//увеличение
{
    if(activeImage!= nullptr) {
        zoomUpdate(true);
        qDebug() << "Zoom In";
    }
}
//кнопки кропа изображения закончены






//Фильтры
/*!
 * \brief Обработчик изменения значения слайдера для настройки контраста
 *
 * Функция вызывается при изменении значения слайдера и устанавливает новое значение в переменную ctr,
 * которая используется для управления контрастом.
 *
 * \param value Новое значение слайдера
 */
void MainWindow::on_SliderContrast_valueChanged(int value)//констраст
{
    ctr = value;
}

/*!
 * \brief MainWindow::on_SliderRed_valueChanged
 * Обработчик события изменения значения ползунка для красного цвета
 * \param value новое значение ползунка
    */
void MainWindow::on_SliderRed_valueChanged(int value)//R
{
    r = value;
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}


/*!
 * \brief MainWindow::on_SliderBlue_valueChanged
 * Обработчик события изменения значения ползунка для синего цвета
 * \param value новое значение ползунка
    */
void MainWindow::on_SliderBlue_valueChanged(int value)//G
{
    b = value;
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}

/*!
 * \brief MainWindow::on_SliderGreen_valueChanged
 * Обработчик события изменения значения ползунка для зеленого цвета
 * \param value новое значение ползунка
    */
void MainWindow::on_SliderGreen_valueChanged(int value)//B
{
    g = value;
    QColor color = QColor(r, g, b);
    QString a1 = QString("background-color: %1").arg(color.name());
    ui->CUBE->setStyleSheet(a1);
}

/*!
 * \brief MainWindow::on_ApplyButton_clicked Применить изменения изображения при нажатии кнопки
 *
 * Функция, выполняемая при нажатии на кнопку "Применить". Применяет цветовую маску к изображению, обновляет
 * массив предпросмотра, обновляет элемент pixmapItemPrev на экране, получает цветовую палитру
 * изображения и ее приоритеты, обновляет палитру и запускает функцию изменения масштаба изображения.
 */
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
         on_actionZoom_Adapt_triggered();
    }
}

//Фильбтры закончены
/*!
 * \brief Обработчик действия при изменении размера изображения предпросмотра изображения.
 * Если активное изображение не равно nullptr, рассчитываем смещение для центрирования изображения для предпросмотра.
 * Затем устанавливаем новую позицию для центрирования изображения.
 */
void MainWindow::on_actionZoom_Adapt_triggered()
{
    if (activeImage != nullptr)
    {


        // Расчет смещения для центрирования изображения для предпросмотра
        QPointF viewportCenter = ui->graphicsView_3->viewport()->rect().center();
        QPointF sceneCenter = ui->graphicsView_3->mapToScene(viewportCenter.toPoint());
        QPointF offset = sceneCenter - pixmapItemPrev->sceneBoundingRect().center();

        // Установка новой позиции для центрирования изображения
        pixmapItemPrev->setPos(pixmapItemPrev->pos() + offset);
    }
}
//Фильбтры закончены
/*!
 * \brief Обработчик действия при изменении размера изображения основного изображения.
 * Если активное изображение не равно nullptr, рассчитываем смещение для центрирования изображения для основного.
 * Затем устанавливаем новую позицию для центрирования изображения.
 */
void MainWindow::on_actionZoom_Adapt_triggered2()
{
    if (activeImage != nullptr)
    {

        // Рассчитываем смещение для центрирования изображения для основного окна
        QPointF viewportCenter = ui->graphicsView->viewport()->rect().center();
        QPointF sceneCenter = ui->graphicsView->mapToScene(viewportCenter.toPoint());
        QPointF offset = sceneCenter - pixmapItem->sceneBoundingRect().center();

        // Рассчитываем новую позицию для центрирования изображения
        QPointF newOffset = pixmapItem->pos() + offset;

        // Центрируем изображение по центру холста
        pixmapItem->setPos(newOffset);

        // Устанавливаем новую позицию для изображения в центре
        pixmapItem->update(newOffset.x(), newOffset.y(), pixmapItem->pixmap().width(), pixmapItem->pixmap().height());


    }
}

/*!
* \brief MainWindow::on_action Image_size_triggered - Функция для обработки триггера действия по изменению размера изображения
*
* Эта функция запускается, когда пользователь хочет изменить размер изображения.
* Сначала программа настраивает масштаб, затем, при наличии активного изображения, запрашивает у пользователя значения ширины и высоты в определенном диапазоне.
* Ширина и высота проверяются, чтобы убедиться, что они находятся в определенных пределах.
* Затем он изменяет размер массива пикселей изображения, чтобы приспособиться к новым размерам, и применяет изменения к активному окну.
* Наконец, он центрирует изображение на экране, снова активируя функцию адаптации масштаба.
*/
void MainWindow::on_actionImage_size_triggered()
{
     on_actionZoom_Adapt_triggered();
    if (activeImage != nullptr) {
        bool ok = false;
        QList<QString> fields = {"Width", "Height"};
        QList<int> values = InputDialog::getFields(this, fields, 1, 10000, 100, &ok);

        if (ok) {

            int x;
            int y;

            x = values[0];
            y = values[1];

            if (x < 3)
                x = 3;
            if (y < 3)
                y = 3;

            if(x>10000)
                x=10000;
            if(y>10000)
                y=10000;

            std::vector<pixel> newPixelBuffer = previewImage->getPixelArr();
            std::vector<pixel> &newPixelArr = previewImage->getPixelArr() ;
            newPixelArr.resize(y*x);

            double x_ratio = previewImage->getW() / (double) x;
            double y_ratio = previewImage->getH() / (double) y;
            double px;
            double py;

            for (int i = 0; i < y; i++)
                for (int j = 0; j < x; j++) {
                    px = floor(j * x_ratio);
                    py = floor(i * y_ratio);
                    newPixelArr[i * x + j] = newPixelBuffer[(int) ((py * previewImage->getW()) + px)];
                }
            previewImage->setW(x);

            previewImage->setH(y);


            // Применение изменений к активному окну
            previewImage -> updateArr();
            pixmapItemPrev->setPixmap(QPixmap::fromImage(previewImage->getQImage()));


            // Применение масштабирования для центрирования изображения
            on_actionZoom_Adapt_triggered();
        }
    }
}





/*!
* \brief описание MainWindow::on_action Scene_size_triggered - Слот для обработки триггера действия по изменению размера сцены
*
* Эта функция запускается, когда пользователь хочет изменить размер сцены.
* Сначала программа настраивает масштаб в соответствии с обновленным размером изображения.
* Затем запрашивает у пользователя значения ширины и высоты в определенном диапазоне и проверяет правильность введенных данных.
* Функция изменяет размер сцены и устанавливает минимальный и максимальный размеры изображения соответственно.
* Он обновляет режим видового экрана, чтобы обеспечить полное обновление видового экрана.
* Наконец, он центрирует изображение на экране, снова активируя функцию адаптации масштаба.
*/


void MainWindow::on_actionScene_size_triggered()
{
    on_actionZoom_Adapt_triggered();
    bool ok = false;
    QList<QString> fields = {"Width", "Height"};
    QList<int> values = InputDialog::getFields(this, fields, 1, 10000, 100, &ok);

    if (ok) {
        int newWidth = values[0];
        int newHeight = values[1];

        if (newWidth < 1)
            newWidth = 1;
        if (newHeight < 1)
            newHeight = 1;
        if (newWidth > 1280)
            newWidth = 1280;
        if (newHeight > 720)
            newHeight = 720;

        ui->graphicsView->setMinimumSize(newWidth, newHeight);

        scene.setSceneRect(0, 0, newWidth, newHeight);
        ui->graphicsView->setMaximumSize(newWidth, newHeight);

        // Обновляем вид окна
        ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        // Применяем масштабирование для центрирования изображения
        on_actionZoom_Adapt_triggered();
        on_actionZoom_Adapt_triggered2();

         ui->graphicsView->show();

    }
}
