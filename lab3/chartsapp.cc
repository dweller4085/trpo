#include "chartsapp.hh"

#include <QSplitter>

IoCContainer gIoCContainer;

ChartsApp::ChartsApp() {
    auto splitter = new QSplitter {this};
    this->fileView = new FileView {this};
    this->chartView = new ChartView {this};

    splitter->addWidget(fileView);
    splitter->addWidget(chartView);

    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 5);

    setCentralWidget(splitter);

    setMinimumHeight(360);
}
