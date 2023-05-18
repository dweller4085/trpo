#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QObject>
#include <QtGui>
#include <QTextCodec>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include "graphics.hh"

class MainWindow : public QWidget { Q_OBJECT
    Scene * scene;
    QTextCodec * codec;
    QPushButton * exitButton;

public:
    MainWindow();
};

#endif // MAINWINDOW_HH
