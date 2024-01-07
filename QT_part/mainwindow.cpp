#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPalette>
#include <QSerialPort>
#include <QSerialPortInfo>
//#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Окно настроек COM
    setting_window = new SettingWindow();
    // Окно графиков
    plot_window = new plot();
    // Управление БД
    db = new DbManager;

    // Фиксированный размер окна
    setFixedSize(width(), height());
    setWindowTitle("Weather Monitor");
    //setWindowIcon(QIcon("D:/projects/WeatherMonitor/QT_part/res/img/icon.ico"));

    // Установка фона *******************************************************

    QPixmap bkgnd("D:/projects/WeatherMonitor/QT_part/res/img/background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);

    //***********************************************************************

    // Создание Меню ********************************************************

    QMenu *menu_1, *menu_2;

    menu_1 = menuBar()->addMenu("Меню");
    // Сохранить измерения
    QPixmap savepix("D:/projects/WeatherMonitor/QT_part/res/img/save.png");
    QAction* seve_measurements = new QAction(savepix,"Сохранить измерения", this);
    menu_1->addAction(seve_measurements);
    connect(seve_measurements, &QAction::triggered, this, &MainWindow::on_save_measurement_triggered);

    // Построить график
    QPixmap plotpix("D:/projects/WeatherMonitor/QT_part/res/img/graph.png");
    QAction* plot_graph = new QAction(plotpix, "Построить график", this);
    menu_1->addAction(plot_graph);
    connect(plot_graph, &QAction::triggered, this, &MainWindow::on_plot_measurement_triggered);

    // Настройка COM
    QPixmap compix("D:/projects/WeatherMonitor/QT_part/res/img/comport.png");
    QAction* set_com = new QAction(compix, "Настройка COM", this);
    connect(set_com, &QAction::triggered, this, &MainWindow::on_set_com_triggered);
    menu_1->addAction(set_com);

    menu_2 = menuBar()->addMenu("Справка");
    // О программе
    QPixmap aboutpix("D:/projects/WeatherMonitor/QT_part/res/img/about.png");
    QAction* about = new QAction(aboutpix, "О программе", this);
    menu_2->addAction(about);
    connect(about, &QAction::triggered, this, &MainWindow::on_about_triggered);

    //***********************************************************************

    // Настройка COM ********************************************************

    serial = setting_window->getComSettings();
    //serial->open(QIODevice::ReadOnly);
    connect(serial,&QSerialPort::readyRead,this ,&MainWindow::serialRecieve);

    // **********************************************************************
}

MainWindow::~MainWindow()
{
    //qDebug() << serial->portName();
    //qDebug() << serial->BaudRate();
    delete ui;
    serial->close();
    delete serial;
    //qDebug() << "Destructor";
}

void MainWindow::serialRecieve()
{   
    QByteArray dataBA = serial->readAll();
    QString data(dataBA);

    QList<QString> splitMsg;

    code = "***";
    codeSize = code.size();

    buffer.append(data);
    int index = buffer.indexOf(code);

    if(index != -1)
    {
       QString message = buffer.mid(0,index);
       buffer.remove(0,index+codeSize);
       splitMsg = message.split(" ");

       qDebug() << serial->portName() << ": " << message;
       //qDebug() << "Temp: " << splitMsg[0];
       //qDebug() << "Hum: " << splitMsg[1];
       ui->lcdNumber->display(splitMsg[0]);
       ui->lcdNumber_2->display(splitMsg[1]);
    }
}

void MainWindow::on_save_measurement_triggered()
{
    ui->statusbar->showMessage("Измерения сохранены!");

    //ui->lcdNumber->bindingStorage();
    //db.viewDb();
    //qDebug() << ui->lcdNumber->value();
    db->addMeasurement(ui->lcdNumber->value(), ui->lcdNumber_2->value());
}

void MainWindow::on_plot_measurement_triggered()
{
    //db.viewDb();
    QVector<QString> date = db->getDate();
    QVector<double> temp = db->getTemp();
    QVector<double> hum = db->getHum();
    //qDebug() << date;
    //qDebug() << temp;
    //qDebug() << hum;

    if(date.size() < 10)
        QMessageBox::critical(this, "Внимание","Мало записей измерений!");
    else {
        // Создаем график
        plot_window->plotGraph(date, temp, hum);
        plot_window->show();
    }
    //date.clear();
    //temp.clear();
    //hum.clear();
}

void MainWindow::on_set_com_triggered()
{
  //qDebug() << setting_window->getString();
  //serial = setting_window->getComSettings();
  //qDebug() << serial->portName();
  setting_window->show();
}

void MainWindow::on_about_triggered()
{
    //QPixmap aboutpix("D:/projects/WeatherMonitor/QT_part/res/img/about.png");

    QMessageBox msgBox;
    msgBox.setText("Программа показывает текущие температуру и влажность.\n"
                   "Период считывания данных 5 сек.\n"
                   "Для корректной работы небходимо выбрать и настроить COM порт.");

    //msgBox.setIconPixmap(aboutpix);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}



