#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

struct ColorScheme {
    enum { Light, BW, BlueCerulean, } scheme;

    explicit operator QString() const {
        QString s;

        switch (scheme) {
            case Light: s = "Light"; break;
            case BW: s = "BW"; break;
            case BlueCerulean: s = "Blue Cerulean"; break;
            default: s = ""; break;
        }

        return s;
    }
};

struct ChartType {
    enum { Pie, Bar, Line, } type;

    explicit operator QString() const {
        QString s;

        switch (type) {
            case Pie: s = "Pie"; break;
            case Bar: s = "Bar"; break;
            case Line: s = "Line"; break;
            default: s = ""; break;
        }

        return s;
    }
};

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

struct NullChart: IChartTemplate {};

QVector<ChartType> inline static const gSupportedChartTypes {{ChartType::Pie}, {ChartType::Bar}, {ChartType::Line}};
QVector<ColorScheme> inline static const gSupportedColorSchemes {{ColorScheme::Light}, {ColorScheme::BW}, {ColorScheme::BlueCerulean}};
