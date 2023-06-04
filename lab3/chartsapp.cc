#include "chartsapp.hh"

#include <QSplitter>

ChartsApp::ChartsApp() {
    auto splitter = new QSplitter {this};
    splitter->addWidget(new FileView {this});
    //splitter->addWidget(new ChartView {this});
    setCentralWidget(splitter);
}
