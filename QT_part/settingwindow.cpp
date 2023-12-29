#include"mainwindow.h"
#include"settingwindow.h"

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QStatusBar>
#include <QMessageBox>

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent)
{
  setFixedSize(400, 500);
  setWindowTitle("Settings");

  //QHBoxLayout *hbox = new QHBoxLayout(this);
  //QHBoxLayout *hbox = new QHBoxLayout(this);
  QGridLayout* grid = new QGridLayout(this);
  grid->setSpacing(2);

  // Доступные порты
  QLabel *label_1 = new QLabel("COM:");
  QComboBox *combo_box_1 = new QComboBox();
  QList<QSerialPortInfo> ports = info.availablePorts();
  QList<QString> stringPorts;
  for(int i = 0 ; i < ports.size() ; i++)
      stringPorts.append(ports.at(i).portName());

  combo_box_1->addItems(stringPorts);
  grid->addWidget(label_1, 0,0);
  grid->addWidget(combo_box_1, 0,1);

  // Доступные скорости
  QLabel *label_2 = new QLabel("BaudRates:");
  QComboBox *combo_box_2 = new QComboBox();
  QList<qint32> baudRates = info.standardBaudRates();
  QList<QString> stringBaudRates;
  for(int i = 0 ; i < baudRates.size() ; i++)
        stringBaudRates.append(QString::number(baudRates.at(i)));

  combo_box_2->addItems(stringBaudRates);
  grid->addWidget(label_2, 1,0);
  grid->addWidget(combo_box_2, 1,1);

  // Бит данных
  QLabel *label_3 = new QLabel("Data bits:");
  QComboBox *combo_box_3 = new QComboBox();
  combo_box_3->addItem("5");
  combo_box_3->addItem("6");
  combo_box_3->addItem("7");
  combo_box_3->addItem("8");
  grid->addWidget(label_3, 2,0);
  grid->addWidget(combo_box_3, 2,1);

  // Стоп бит
  QLabel *label_4 = new QLabel("Stop bits:");
  QComboBox *combo_box_4 = new QComboBox();
  combo_box_4->addItem("1 Bit");
  combo_box_4->addItem("1,5 Bits");
  combo_box_4->addItem("2 Bits");
  grid->addWidget(label_4, 3,0);
  grid->addWidget(combo_box_4, 3,1);

  // Четность
  QLabel *label_5 = new QLabel("Parities:");
  QComboBox *combo_box_5 = new QComboBox();
  combo_box_5->addItem("No Parity");
  combo_box_5->addItem("Even Parity");
  combo_box_5->addItem("Odd Parity");
  combo_box_5->addItem("Mark Parity");
  combo_box_5->addItem("Space Parity");
  grid->addWidget(label_5, 4,0);
  grid->addWidget(combo_box_5, 4,1);

  // Flow Controls
  QLabel *label_6 = new QLabel("Flow Controls:");
  QComboBox *combo_box_6 = new QComboBox();
  combo_box_6->addItem("No Flow Control");
  combo_box_6->addItem("Hardware Flow Control");
  combo_box_6->addItem("Software Flow Control");
  grid->addWidget(label_6, 5,0);
  grid->addWidget(combo_box_6, 5,1);

  QPushButton *save_btn = new QPushButton("Сохранить");
  grid->addWidget(save_btn, 6,1);
  connect(save_btn,&QPushButton::clicked,this,&SettingWindow::on_pushButton_clicked);

  setLayout(grid);

  //serialPort->setPortName("com1");
}

SettingWindow::~SettingWindow()
{

}


QSerialPort* SettingWindow::getComSettings()
{
    serialPort = new QSerialPort(this);
    serialPort->setPortName("com3");
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadOnly);

    return serialPort;
}

void SettingWindow::on_pushButton_clicked()
{
    //MainWindow::serial = serial;



    QMessageBox msgBox;
    msgBox.setText("Настройки сохранены");
    msgBox.exec();
}
