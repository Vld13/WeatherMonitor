#include "mainwindow.h"

#include <QApplication>
#include <QLayout>
#include <QPalette>
#include <QDebug>
#include <QDate>

#include <QSerialPort>
#include <QSerialPortInfo>

#include "plot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    main_window.show();

    return a.exec();
}
