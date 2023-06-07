#include "chartsapp.hh"

#include <QSplitter>
#include <iostream>
#include "filereadingstrategy.hh"
#include "iocc.hh"

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

    QObject::connect(fileView, &FileView::fileSelected, updateStrategy);
    QObject::connect(fileView, &FileView::fileSelected, this, &ChartsApp::onFileSelected);
}

void ChartsApp::onFileSelected(QFileInfo const& info) {
    auto readingStrategy = gIoCContainer.getService<IFileReadingStrategy>();

    if (readingStrategy->read(info.absoluteFilePath(), this->data)) {
        emit ChartsApp::dataChanged(data);
    } else {
        emit ChartsApp::dataInvalidated(info);
    }
}
