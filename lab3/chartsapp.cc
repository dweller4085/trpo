#include "chartsapp.hh"

#include <QSplitter>

ChartsApp::ChartsApp() {
    auto splitter = new QSplitter {this};
    this->fileView = new FileView {this};
    this->chartView = new ChartView {this};

    splitter->addWidget(fileView);
    splitter->addWidget(chartView);

    setCentralWidget(splitter);

    setMinimumHeight(360);
}
