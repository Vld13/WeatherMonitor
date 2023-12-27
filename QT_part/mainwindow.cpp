#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPalette>
#include <QSerialPort>
#include <QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установка фона *******************************************************
    QPixmap bkgnd("D:/projects/WeatherMonitor/QT_part/res/img/background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    //***********************************************************************

    // Настройка COM ********************************************************
    serial = new QSerialPort(this);
    serial->setPortName("com3");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    connect(serial,SIGNAL(readyRead()),this,SLOT(serialRecieve()));

    //foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    //{
     //QSerialPort port;
     //port.setPort(info);
     //if(port.open(QIODevice::ReadWrite))
     //{
      //   qDebug() << "Name : " << info.portName();
     //}
    //}


    //***********************************************************************




}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
    qDebug() << "Destructor";
}

void MainWindow::serialRecieve()
{
    //QByteArray arr;
    QString str;
    QStringList str1;

    //arr = serial->readAll();
    str = serial->readAll();
    str1 = str.split(" ");
    //qDebug() << str1.size();

    if(str1.size()==2)
    {
       // qDebug() << "msg0: " << str1[0];
       // qDebug() << "msg1: " << str1[1];
        ui->lcdNumber->display(str1[0]);
        ui->lcdNumber_2->display(str1[1]);
    }

    /*
    try
    {
        str1 = str.split(" ");
        //arr = serial->readLine();
        ui->lcdNumber->display(str);
        qDebug() << "msg0: " << str1[0];
        qDebug() << "msg1: " << str1[1];
    }
    catch(const std::exception& e)
    {
        qDebug() << "Исключение: " << e.what();
    }
    catch(...)
    {
       qDebug() << "Исключение";
    }
    */


}

void MainWindow::on_save_measurement_triggered()
{
    ui->statusbar->showMessage("Измерения сохранены!");
    //QMessageBox::about(this, " ", "Измерения сохранены!");
    //QLCDNumber::Mode mod = ui->lcdNumber->mode();
    //QLCDNumber::SegmentStyle styl = ui->lcdNumber->segmentStyle();
    ui->lcdNumber->display(50);
    //ui->lcdNumber->setDigitCount(50);

    //ui->lcdNumber->setSegmentStyle(styl);
    //ui->lcdNumber->setMode(mod);

}


void MainWindow::on_about_triggered()
{
    QMessageBox::about(this, " ", "Программа показывает текущие температуру и влажность.\n"
                                  "Период считывания данных 5 сек.\n"
                                  "Для корректной работы небходимо выбрать COM порт.\n");
}



