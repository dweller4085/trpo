#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum class ColorScheme { Light, BW, BlueCerulean };
enum class ChartType { PieChart, BarChart, LineChart };

struct IChartTemplate {
    QChart * operator () (ChartData const& cd, ColorScheme const& cs);

protected:
    virtual QAbstractSeries * generateSeries(ChartData const&) = 0;
    virtual QChart * generateChart() = 0;
};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

QVector<ChartType> inline static const gSupportedChartTypes {ChartType::PieChart, ChartType::BarChart, ChartType::LineChart};
QVector<ColorScheme> inline static const gSupportedColorSchemes {ColorScheme::Light, ColorScheme::BW, ColorScheme::BlueCerulean};
