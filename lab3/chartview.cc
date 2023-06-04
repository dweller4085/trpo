#include "chartview.hh"
#include <QVBoxLayout>
#include <QLabel>

ChartView::ChartView(QWidget * parent): QWidget {parent} {
    auto layout = new QVBoxLayout {this};
    layout->addWidget(new QLabel {"heelo", this});
}
