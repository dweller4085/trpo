#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.hh"

MainWindow::MainWindow(QWidget * parent):
    QWidget {parent},
    codec {QTextCodec::codecForName("UTF-8")},
    onesCounter {
        new QLabel {codec->toUnicode("Cчет по 1"), this},
        new Counter {0, 5, this}
    },
    fivesCounter {
        new QLabel {codec->toUnicode("Cчет по 5"), this},
        new Counter {this}
    },
    incrementButton {new QPushButton {"+1", this}},
    exitButton {new QPushButton {codec->toUnicode("Выход"), this}}
{
    this->setWindowTitle(codec->toUnicode("Счетчик"));

    QHBoxLayout * lables = new QHBoxLayout();
    lables->addWidget(onesCounter.label);
    lables->addWidget(fivesCounter.label);

    QHBoxLayout * edits = new QHBoxLayout();
    edits->addWidget(onesCounter.counter);
    edits->addWidget(fivesCounter.counter);

    QHBoxLayout * buttons = new QHBoxLayout();
    buttons->addWidget(incrementButton);
    buttons->addWidget(exitButton);

    QVBoxLayout * mainLayout = new QVBoxLayout {this};
    mainLayout->addLayout(lables);
    mainLayout->addLayout(edits);
    mainLayout->addLayout(buttons);

    connect(incrementButton, &QPushButton::clicked, onesCounter.counter, &Counter::increment);
    connect(onesCounter.counter, &Counter::tick, fivesCounter.counter, &Counter::increment);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
}
