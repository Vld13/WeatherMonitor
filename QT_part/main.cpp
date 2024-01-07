#include "mainwindow.h"

#include <QApplication>
#include <QLayout>
#include <QPalette>
#include <QDebug>
#include <QDate>

#include <QSerialPort>
#include <QSerialPortInfo>

//#include "qcustomplot.h"
//#include "dbmanager.h"
#include "plot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    //plot plot_window;


    main_window.show();
    //plot_window.show();

    return a.exec();
}
