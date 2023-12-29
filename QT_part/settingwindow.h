#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class SettingWindow; }
QT_END_NAMESPACE

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    SettingWindow(QWidget *parent = 0);
    ~SettingWindow();
    QString getString();
    QSerialPort* getComSettings();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_pushButton_clicked();

private :
    QSerialPort* serialPort;
    QSerialPortInfo info;
};

#endif // SETTINGWINDOW_H
