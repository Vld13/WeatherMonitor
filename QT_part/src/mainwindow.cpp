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

    // Окно настроек COM
    setting_window = new SettingWindow();
    // Окно графиков
    plot_window = new plot();
    // Управление БД
    db = new DbManager;

    // Фиксированный размер окна
    setFixedSize(width(), height());
    setWindowTitle("Weather Monitor");

    // Установка фона *******************************************************

    QPixmap bkgnd("add/path/to/background");
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
    connect(serial,&QSerialPort::readyRead,this ,&MainWindow::serialRecieve);

    // **********************************************************************
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;

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
       ui->lcdNumber->display(splitMsg[0]);
       ui->lcdNumber_2->display(splitMsg[1]);
    }
}

void MainWindow::on_save_measurement_triggered()
{
    ui->statusbar->showMessage("Измерения сохранены!");

    db->addMeasurement(ui->lcdNumber->value(), ui->lcdNumber_2->value());
}

void MainWindow::on_plot_measurement_triggered()
{
    QVector<QString> date = db->getDate();
    QVector<double> temp = db->getTemp();
    QVector<double> hum = db->getHum();

    if(date.size() < 10)
        QMessageBox::critical(this, "Внимание","Мало записей измерений!");
    else {
        // Создаем график
        plot_window->plotGraph(date, temp, hum);
        plot_window->show();
    }
}

void MainWindow::on_set_com_triggered()
{
  setting_window->show();
}

void MainWindow::on_about_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Программа показывает текущие температуру и влажность.\n"
                   "Есть возможность сохранение данных в БД(SQLITE).\n"
                   "Для корректной работы небходимо выбрать и настроить COM порт.");

    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}



