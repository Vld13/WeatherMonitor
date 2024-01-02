#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include"settingwindow.h"
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_save_measurement_triggered();
    void on_plot_measurement_triggered();
    void on_set_com_triggered();
    void on_about_triggered();
    void serialRecieve();

private:
    Ui::MainWindow* ui;
    SettingWindow* setting_window;
    QSerialPort* serial;
    DbManager db;
    QString buffer;
    QString code;
    int codeSize;

};
#endif // MAINWINDOW_H
