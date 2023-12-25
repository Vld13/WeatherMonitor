#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    // Фиксированный размер окна
    main_window.setFixedSize(main_window.geometry().width(),main_window.geometry().height());
    main_window.setWindowTitle("Weather Monitor");
    //main_window.setWindowIcon(QIcon("D:/projects/WeatherMonitor/QT_part/res/img/icon.ico"));

    main_window.show();
    return a.exec();
}
