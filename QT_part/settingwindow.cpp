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
  setFixedSize(400, 300);
  setWindowTitle("Settings");

  QGridLayout* grid = new QGridLayout(this);
  grid->setSpacing(1);

  // Доступные порты
  QLabel *label_1 = new QLabel("COM:");
  // QComboBox *combo_box_1 = new QComboBox();
  combo_box_1 = new QComboBox();
  QList<QSerialPortInfo> ports = info.availablePorts();
  QList<QString> stringPorts;
  for(int i=0;i<ports.size();i++)
      stringPorts.append(ports.at(i).portName());

  combo_box_1->addItems(stringPorts);
  grid->addWidget(label_1, 0,0);
  grid->addWidget(combo_box_1, 0,1);

  //qDebug() << combo_box_1->currentText();

  // Доступные скорости
  QLabel *label_2 = new QLabel("BaudRates:");
  //QComboBox *combo_box_2 = new QComboBox();
  combo_box_2 = new QComboBox();
  QList<qint32> baudRates = info.standardBaudRates();
  QList<QString> stringBaudRates;
  for(int i = 0 ; i < baudRates.size() ; i++)
        stringBaudRates.append(QString::number(baudRates.at(i)));

  combo_box_2->addItems(stringBaudRates);
  grid->addWidget(label_2, 1,0);
  grid->addWidget(combo_box_2, 1,1);

  // Бит данных
  QLabel *label_3 = new QLabel("Data bits:");
  //QComboBox *combo_box_3 = new QComboBox();
  combo_box_3 = new QComboBox();
  combo_box_3->addItem("5");
  combo_box_3->addItem("6");
  combo_box_3->addItem("7");
  combo_box_3->addItem("8");
  grid->addWidget(label_3, 2,0);
  grid->addWidget(combo_box_3, 2,1);

  // Стоп бит
  QLabel *label_4 = new QLabel("Stop bits:");
  //QComboBox *combo_box_4 = new QComboBox();
  combo_box_4 = new QComboBox();
  combo_box_4->addItem("1 Bit");
  combo_box_4->addItem("1,5 Bits");
  combo_box_4->addItem("2 Bits");
  grid->addWidget(label_4, 3,0);
  grid->addWidget(combo_box_4, 3,1);

  // Четность
  QLabel *label_5 = new QLabel("Parities:");
  //QComboBox *combo_box_5 = new QComboBox();
  combo_box_5 = new QComboBox();
  combo_box_5->addItem("No Parity");
  combo_box_5->addItem("Even Parity");
  combo_box_5->addItem("Odd Parity");
  combo_box_5->addItem("Mark Parity");
  combo_box_5->addItem("Space Parity");
  grid->addWidget(label_5, 4,0);
  grid->addWidget(combo_box_5, 4,1);

  // Flow Controls
  QLabel *label_6 = new QLabel("Flow Controls:");
  //QComboBox *combo_box_6 = new QComboBox();
  combo_box_6 = new QComboBox();
  combo_box_6->addItem("No Flow Control");
  combo_box_6->addItem("Hardware Flow Control");
  combo_box_6->addItem("Software Flow Control");
  grid->addWidget(label_6, 5,0);
  grid->addWidget(combo_box_6, 5,1);

  QPushButton *save_btn = new QPushButton("Сохранить");
  grid->addWidget(save_btn, 7,1);
  connect(save_btn,&QPushButton::clicked,this,&SettingWindow::on_pushButton_clicked);

  //grid->setRowStretch(7,2);

  setLayout(grid);

  //serialPort->setPortName("com1");
}

SettingWindow::~SettingWindow()
{

}

QSerialPort* SettingWindow::getComSettings()
{
    // Настройка COM по умолчанию
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
    // Установка параметров COM с меню настроек

    QString portName = combo_box_1->currentText();
    serialPort->setPortName(portName);

    QString stringbaudRate = combo_box_2->currentText();
    int intbaudRate = stringbaudRate.toInt();
    serialPort->setBaudRate(intbaudRate);

    QString dataBits = combo_box_3->currentText();
    if(dataBits == "5 Bits")
      serialPort->setDataBits(QSerialPort::Data5);
     else if((dataBits == "6 Bits"))
       serialPort->setDataBits(QSerialPort::Data6);
     else if(dataBits == "7 Bits")
       serialPort->setDataBits(QSerialPort::Data7);
     else if(dataBits == "8 Bits")
       serialPort->setDataBits(QSerialPort::Data8);

    QString stopBits = combo_box_4->currentText();
    if(stopBits == "1 Bit")
     serialPort->setStopBits(QSerialPort::OneStop);
    else if(stopBits == "1,5 Bits")
     serialPort->setStopBits(QSerialPort::OneAndHalfStop);
    else if(stopBits == "2 Bits")
     serialPort->setStopBits(QSerialPort::TwoStop);

    QString parity = combo_box_5->currentText();
    if(parity == "No Parity")
      serialPort->setParity(QSerialPort::NoParity);
    else if(parity == "Even Parity")
      serialPort->setParity(QSerialPort::EvenParity);
    else if(parity == "Odd Parity")
      serialPort->setParity(QSerialPort::OddParity);
    else if(parity == "Mark Parity")
      serialPort->setParity(QSerialPort::MarkParity);
    else if(parity == "Space Parity")
        serialPort->setParity(QSerialPort::SpaceParity);


    QString flowControl = combo_box_6->currentText();
    if(flowControl == "No Flow Control")
      serialPort->setFlowControl(QSerialPort::NoFlowControl);
    else if(flowControl == "Hardware Flow Control")
      serialPort->setFlowControl(QSerialPort::HardwareControl);
    else if(flowControl == "Software Flow Control")
      serialPort->setFlowControl(QSerialPort::SoftwareControl);

    //qDebug() << combo_box_1->currentText();

    QMessageBox msgBox;
    msgBox.setWindowTitle(" ");
    msgBox.setText("Настройки сохранены");
    msgBox.exec();
}
