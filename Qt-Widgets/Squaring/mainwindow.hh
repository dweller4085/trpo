#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QObject>
#include <QtGui>
#include <QTextCodec>
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class MainWindow : public QWidget { Q_OBJECT
    QTextCodec *  codec;
    QFrame *      frame;
    QLabel *      inputLabel;
    QLabel *      outputLabel;
    QLineEdit *   inputEdit;
    QLineEdit *   outputEdit;
    QPushButton * nextButton;
    QPushButton * exitButton;

public:
    explicit MainWindow(QWidget * parent);
    MainWindow(): MainWindow {nullptr} {}

public slots:
    void reset();
    void square();
};

#endif // MAINWINDOW_HH
