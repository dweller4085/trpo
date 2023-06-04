#include <QApplication>
#include <QFileDialog>
#include <MKB/aliases.h>

#include "chartsapp.hh"


#include <QFile>

int main (int argc, char ** argv) {
    QApplication app {argc, argv};
    ChartsApp window;
    window.show();



    return app.exec();
}
