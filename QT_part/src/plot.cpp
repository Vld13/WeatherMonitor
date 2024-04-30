#include "plot.h"
#include "ui_plot.h"
#include "qcustomplot.h"

plot::plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plot)
{
    ui->setupUi(this);

    setWindowTitle("Plot");
}

plot::~plot()
{
    delete ui;
}

void plot::plotGraph(QVector<QString> date, QVector<double> temp, QVector<double> hum)
{
    //qDebug() << date;
    //qDebug() << temp;
    //qDebug() << hum;

    // Переворачиваем векторы
    std::reverse(std::begin(date), std::end(date));
    std::reverse(std::begin(temp), std::end(temp));
    std::reverse(std::begin(hum), std::end(hum));

    // Очищаем все графики
    ui->widget->clearGraphs();
    ui->widget_2->clearGraphs();

    // Добавляем графики в widget
    ui->widget->addGraph();
    ui->widget_2->addGraph();

    // Стиль линии ************************************************************

    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    ui->widget->graph(0)->setPen(pen);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget_2->graph(0)->setLineStyle(QCPGraph::lsLine);

    // Кружочки на точках
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->widget_2->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    //*************************************************************************

    // Ось Х ******************************************************************

    QVector<double> x;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

    x << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;

    // График температур
    textTicker->addTicks(x, date);
    ui->widget->xAxis->setTicker(textTicker);
    ui->widget->xAxis->setTickLabelRotation(60);
    ui->widget->xAxis->setSubTicks(false);
    ui->widget->xAxis->setRange(0, 11);
    //ui->widget->xAxis->setLabel("Дата");

    // График влажности
    textTicker->addTicks(x, date);
    ui->widget_2->xAxis->setTicker(textTicker);
    ui->widget_2->xAxis->setTickLabelRotation(60);
    ui->widget_2->xAxis->setSubTicks(false);
    ui->widget_2->xAxis->setRange(0, 11);
    //ui->widget->xAxis->setLabel("Дата");

    //*************************************************************************

    // Ось У ******************************************************************

    ui->widget->yAxis->setLabel("Температура, °C");
    ui->widget->yAxis->setRange(0, 50);

    ui->widget_2->yAxis->setLabel("Влажность, %");
    ui->widget_2->yAxis->setRange(0, 100);

    //*************************************************************************


    // Устанавливаем данные
    ui->widget->graph(0)->setData(x, temp);
    ui->widget_2->graph(0)->setData(x, hum);

    // Строим график
    ui->widget->replot();
    ui->widget_2->replot();
}
