#include "mainwindow.hh"

#include <QSplitter>

#include "data.hh"
#include "iocc.hh"

MainWindow::MainWindow() {
    auto splitter = new QSplitter {this};
    this->fileView = new FileView {this};
    this->chartView = new ChartView {this};

    splitter->addWidget(fileView);
    splitter->addWidget(chartView);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    splitter->setHandleWidth(1);

    setCentralWidget(splitter);

    setMinimumHeight(400);

    QObject::connect(fileView, &FileView::fileSelected, updateStrategy);
    QObject::connect(fileView, &FileView::fileSelected, this, &MainWindow::onFileSelected);
}

void MainWindow::onFileSelected(QFileInfo const& info) {
    auto readingStrategy = gIoCContainer.getService<IDataReadingStrategy>();
    auto errorMsg = QString {};

    if (readingStrategy->read(info.absoluteFilePath(), this->data, errorMsg)) {
        emit MainWindow::dataChanged(data);
    } else {
        emit MainWindow::dataInvalidated(errorMsg);
    }
}
