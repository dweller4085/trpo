#ifndef CHARTSAPP_HH
#define CHARTSAPP_HH

#include "fileview.hh"
#include "chartview.hh"
#include "common.hh"

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QFileInfo>

class ChartsApp: public QMainWindow { Q_OBJECT
public:
    ChartsApp();

signals:
    void dataChanged(ChartData const&);
    void dataInvalidated(QFileInfo const&);

public slots:
    void onFileSelected(QFileInfo const&);

private:
    FileView * fileView;
    ChartView * chartView;
    ChartData data;
};

#endif // CHARTSAPP_HH
