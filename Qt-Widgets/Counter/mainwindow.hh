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
    QLabel * label1;
    QLabel * label2;
    Counter * edit1;
    Counter * edit2;
    QPushButton * calcbutton;
    QPushButton * exitbutton;

public:
    MainWindow(QWidget * parent);
    MainWindow(): MainWindow {nullptr} {}
};

#endif // MAINWINDOW_HH
