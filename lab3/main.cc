#include <QApplication>
#include <QFileDialog>

#include "mainwindow.hh"
#include "data.hh"
#include "charts.hh"
#include "iocc.hh"

IoCContainer gIoCContainer;

int main (int argc, char ** argv) {
    //gIoCContainer.registerService<IFileReadingStrategy, NullStrategy>();
    //gIoCContainer.registerService<IChartTemplate, NullChart>();

    QApplication app {argc, argv};
    MainWindow window;
    window.show();

    return app.exec();
}
