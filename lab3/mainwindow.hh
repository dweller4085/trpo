#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QWidget>
#include <QMainWindow>

struct FileView: QWidget {
    explicit FileView(QWidget * parent): QWidget {parent} {}
};

struct Plotter: QWidget {
    explicit Plotter(QWidget * parent): QWidget {parent} {}
};

class MainWindow: public QMainWindow { Q_OBJECT
public:
    MainWindow();
};

#endif // MAINWINDOW_HH
