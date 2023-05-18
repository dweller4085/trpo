#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.hh"

MainWindow::MainWindow():
    scene {new Scene {this}},
    codec {QTextCodec::codecForName("UTF-8")},
    exitButton {new QPushButton {this}}
{
    QWidget::setWindowTitle(codec->toUnicode("Event handling"));
    exitButton->setText(codec->toUnicode("Exit"));

    auto layout = new QVBoxLayout {this};
    layout->addWidget(scene);
    layout->addWidget(exitButton);

    QObject::connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
}
