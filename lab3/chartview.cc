#include "chartview.hh"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

ChartView::ChartView(QWidget * parent): QWidget {parent} {
    auto layout = new QVBoxLayout {this};
    auto buttons = new QHBoxLayout {};
    chartView = new QChartView {};
    chartType = new QComboBox {};
    colorScheme = new QComboBox {};
    saveToPDF = new QPushButton {"save to pdf"};
    //chartType->setMinimumWidth(100);
    //colorScheme->setMinimumWidth(100);

    auto series = new QPieSeries {};
    series->append("a", 1);
    series->append("b", 2);
    auto chart = new QChart {};
    chart->addSeries(series);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    buttons->addWidget(chartType);
    buttons->addWidget(colorScheme);
    buttons->addStretch();
    buttons->addWidget(saveToPDF);

    layout->addWidget(chartView);
    layout->addLayout(buttons);

    this->setMinimumWidth(360);
}
