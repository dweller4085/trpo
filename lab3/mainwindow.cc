#include "mainwindow.hh"

#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(): QMainWindow {} {
    setCentralWidget(new QWidget {this});
}

