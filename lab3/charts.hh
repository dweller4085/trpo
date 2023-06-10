#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum ColorScheme { Light, BW, BlueCerulean };
enum ChartType { PieChart, BarChart, LineChart };

struct IChartTemplate {
    QChart * operator () (ChartData const& cd, ColorScheme const& cs) {
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

QString asString(ColorScheme scheme);
QString asString(ChartType type);

QVector<ChartType> inline static const gSupportedChartTypes {ChartType::PieChart, ChartType::BarChart, ChartType::LineChart};
QVector<ColorScheme> inline static const gSupportedColorSchemes {ColorScheme::Light, ColorScheme::BW, ColorScheme::BlueCerulean};
