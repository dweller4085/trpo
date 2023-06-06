#ifndef CHARTTEMPLATE_HH
#define CHARTTEMPLATE_HH

#include "common.hh"
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

struct IChartTemplate {
    QChart * createChart(ChartData const& cd, ColorScheme const& cs) {
        auto series = this->generateSeries(cd);
        auto chart = this->generateChart();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->layout()->setContentsMargins(0, 0, 0, 0);
        chart->setBackgroundRoundness(0);

        // set color scheme ...
        return chart;
    }

protected:
    virtual QAbstractSeries * generateSeries(ChartData const&) = 0;
    virtual QChart * generateChart() = 0;
};

struct BarChart: IChartTemplate {};

struct PieChart: IChartTemplate {};

struct LineChart: IChartTemplate {};

#endif // CHARTTEMPLATE_HH
