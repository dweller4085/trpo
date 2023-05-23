#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
    class MainWindow;
}

class MainWindow: public QMainWindow { Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    QFileSystemModel * fsModel;
};

#endif // MAINWINDOW_HH
