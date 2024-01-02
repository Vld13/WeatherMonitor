#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>


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
    //QComboBox* combo_box_1;

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_pushButton_clicked();

private :
    QSerialPort* serialPort;
    QSerialPortInfo info;
    QComboBox* combo_box_1;
    QComboBox* combo_box_2;
    QComboBox* combo_box_3;
    QComboBox* combo_box_4;
    QComboBox* combo_box_5;
    QComboBox* combo_box_6;
    QList<QComboBox*> combo_box_list;
};

#endif // SETTINGWINDOW_H
