#include "mainwindow.h"
#include <QApplication>
#include <QLayout>
#include <QPalette>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    // Фиксированный размер окна
    main_window.setFixedSize(main_window.geometry().width(),main_window.geometry().height());
    main_window.setWindowTitle("Weather Monitor");
    //main_window.setWindowIcon(QIcon("D:/projects/WeatherMonitor/QT_part/res/img/icon.ico"));

    //QSerialPort serial;
    //QSerialPortInfo port;
    //QString buf;
    //char buffer[50];

    //foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    //{
    // qDebug() << "Name : " << info.portName();
     //qDebug() << "Description : " << info.description();
    // qDebug() << "Manufacturer: " << info.manufacturer();

    // port = info;
    //}

     //QSerialPort serial;
     //serial.setPort(port);
     //serial.readData(buf, 60);
     //serial.baudRateChanged(QSerialPort::Baud115200, QSerialPort::Input);

     //for(;;)
     //{
     //    serial.read(buffer, 50);
     //    qDebug() << "Read : " << buffer;
     //}

    main_window.show();
    return a.exec();
}
