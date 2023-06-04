#ifndef CHARTSAPP_HH
#define CHARTSAPP_HH

#include "fileview.hh"
#include "chartview.hh"
#include "iocc.hh"

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>

static IoCContainer gIoCContainer;

struct ChartData {
    struct Point {
        float t;
        float v;
    };

    QVector<Point> points;
};

struct IFileReadingStrategy {
    virtual ChartData read(QString const& path, bool& success) = 0;
    virtual ~IFileReadingStrategy() = default;
};

struct JSON: IFileReadingStrategy {

};

struct SQLite: IFileReadingStrategy {

};

struct IChartTemplate {
    /* QChart * createChart() {
        // ...
        auto a = stepA();
        auto b = stepB();
        // ...
    } */

protected:
    virtual int stepA() = 0;
    virtual bool stepB() = 0;
};

class BarChart: public IChartTemplate {

};

class ChartsApp: public QMainWindow { Q_OBJECT
public:
    ChartsApp();

private:
    FileView * fileView;
    ChartView * chartView;
    ChartData data;
};

#endif // CHARTSAPP_HH
