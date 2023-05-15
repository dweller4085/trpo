#include <QApplication>
#include <QCoreApplication>
#include <MKB/aliases.h>
#include "mainwindow.hh"

int main (int argc, char ** argv) {
    QApplication app(argc, argv);
    MainWindow window {};
    window.show();
    return app.exec();
}
