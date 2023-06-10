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
    auto chart = new QChart {};
    //chartType->setMinimumWidth(100);
    //colorScheme->setMinimumWidth(100);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameStyle(QFrame::StyledPanel);
    chartView->setChart(chart);

    buttons->addWidget(cbChartType);
    buttons->addWidget(cbColorScheme);
    buttons->addStretch();
    buttons->addWidget(pbSaveToPDF);

    layout->addWidget(chartView);
    layout->addLayout(buttons);

    this->setMinimumWidth(360);
}

void ChartView::onDataChanged(ChartData const& data) {
    // draw/redraw the chart with the template in gIoCC
}

void ChartView::onDataInvalidated(QFileInfo const& data) {
    // change/hide/replace the chartView with a red QLabel in the layout
}
