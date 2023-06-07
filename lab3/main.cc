#include <QApplication>
#include <QFileDialog>

#include "chartsapp.hh"
#include "filereadingstrategy.hh"
#include "charttemplate.hh"
#include "iocc.hh"

IoCContainer gIoCContainer;

int main (int argc, char ** argv) {
    //gIoCContainer.registerService<IFileReadingStrategy, NullStrategy>();
    //gIoCContainer.registerService<IChartTemplate, NullChart>();

    QApplication app {argc, argv};
    ChartsApp window;
    window.show();

    return app.exec();
}
