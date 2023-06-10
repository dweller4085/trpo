#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum ColorScheme { Light, BW, BlueCerulean };
enum ChartType { PieChart, BarChart, LineChart };

struct IChartTemplate {
    QChart * operator () (ChartData const& cd, ColorScheme const& cs);

protected:
    virtual QAbstractSeries * generateSeries(ChartData const&) = 0;
    virtual QChart * generateChart() = 0;
};

// it might actually be the case that other modules do not need to know the concrete classes at all

struct BarChart: IChartTemplate {};
struct PieChart: IChartTemplate {};
struct LineChart: IChartTemplate {};
struct NullChart: IChartTemplate {};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

QVector<ChartType> inline static const gSupportedChartTypes {ChartType::PieChart, ChartType::BarChart, ChartType::LineChart};
QVector<ColorScheme> inline static const gSupportedColorSchemes {ColorScheme::Light, ColorScheme::BW, ColorScheme::BlueCerulean};
