#include "chartsapp.hh"

#include <QSplitter>

#include "iocc.hh"
IoCContainer gIoCContainer;

ChartsApp::ChartsApp() {
    auto splitter = new QSplitter {this};
    this->fileView = new FileView {this};
    this->chartView = new ChartView {this};

    splitter->addWidget(fileView);
    splitter->addWidget(chartView);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

    setCentralWidget(splitter);

    setMinimumHeight(400);

    QObject::connect(fileView, &FileView::fileSelected, this, &ChartsApp::onFileSelected);
}
