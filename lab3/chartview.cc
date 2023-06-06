#include "chartview.hh"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

ChartView::ChartView(QWidget * parent): QWidget {parent} {
    layout = new QVBoxLayout {this};
    chartView = new QChartView {};
    cbChartType = new QComboBox {};
    cbColorScheme = new QComboBox {};
    pbSaveToPDF = new QPushButton {"save to pdf"};
    auto buttons = new QHBoxLayout {};
    //chartType->setMinimumWidth(100);
    //colorScheme->setMinimumWidth(100);

    auto series = new QPieSeries {};
    series->append("a", 1);
    series->append("b", 2);
    auto chart = new QChart {};
    //chart->addSeries(series);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    buttons->addWidget(cbChartType);
    buttons->addWidget(cbColorScheme);
    buttons->addStretch();
    buttons->addWidget(pbSaveToPDF);

    layout->addWidget(chartView);
    layout->addLayout(buttons);

    this->setMinimumWidth(360);
}
