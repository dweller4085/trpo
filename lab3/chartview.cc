#include "chartview.hh"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ChartView::ChartView(QWidget * parent): QWidget {parent} {
    auto layout = new QVBoxLayout {this};
    layout->addWidget(new QLabel {"heelo"});
    auto hlay = new QHBoxLayout {};
    chartType = new QComboBox {};
    //chartType->setMinimumWidth(100);
    colorScheme = new QComboBox {};
    //colorScheme->setMinimumWidth(100);
    saveToPDF = new QPushButton {"save to pdf"};
    hlay->addWidget(chartType);
    hlay->addWidget(colorScheme);
    hlay->addStretch();
    hlay->addWidget(saveToPDF);
    layout->addLayout(hlay);

    //this doesnt work
    //this->sizePolicy().setHorizontalStretch(4);
}
