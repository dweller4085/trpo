#ifndef CHARTSAPP_HH
#define CHARTSAPP_HH

#include "fileview.hh"
#include "chartview.hh"
#include "common.hh"

#include <QMainWindow>

class ChartsApp: public QMainWindow { Q_OBJECT
public:
    ChartsApp();

private:
    FileView * fileView;
    ChartView * chartView;
    ChartData data;
};

#endif // CHARTSAPP_HH
