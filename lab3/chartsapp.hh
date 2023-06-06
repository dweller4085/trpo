#ifndef CHARTSAPP_HH
#define CHARTSAPP_HH

#include "fileview.hh"
#include "chartview.hh"
#include "common.hh"

#include <QMainWindow>
#include <QString>

class ChartsApp: public QMainWindow { Q_OBJECT
public:
    ChartsApp();

public slots:
    //void onFileSelected(QString const&);

private:
    FileView * fileView;
    ChartView * chartView;
    ChartData data;
};

#endif // CHARTSAPP_HH
