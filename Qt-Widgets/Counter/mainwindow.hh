#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QObject>
#include <QtGui>
#include <QTextCodec>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "counter.hh"

class MainWindow : public QWidget { Q_OBJECT
    QTextCodec * codec;
    struct LabeledCounter {
        QLabel * label;
        Counter * counter;
    } onesCounter, fivesCounter;
    QPushButton * incrementButton;
    QPushButton * exitButton;

public:
    MainWindow(QWidget * parent);
    MainWindow(): MainWindow {nullptr} {}
};

#endif // MAINWINDOW_HH
