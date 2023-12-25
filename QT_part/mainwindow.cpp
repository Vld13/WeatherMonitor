#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("D:/projects/WeatherMonitor/QT_part/res/img/background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
    //setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    //setFixedSize(sizeHint());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_save_measurement_triggered()
{
    //ui->statusbar->showMessage("Измерения сохранены!");
    QMessageBox::about(this, " ", "Измерения сохранены!");
}

