#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

namespace Ui {
class plot;
}

class plot : public QWidget
{
    Q_OBJECT

public:
    explicit plot(QWidget *parent = nullptr);
    ~plot();
    void plotGraph(QVector<QString>, QVector<double>, QVector<double>);

private:
    Ui::plot *ui;
};

#endif // PLOT_H
