#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum class ColorScheme { Light, Dark, BlueCerulean, BlackAndWhite };
enum class ChartType { Pie, Bar, Line, Polar };

struct IChartTemplate {
    QChart * build (ChartData const& cd, ColorScheme const& cs);

protected:
    virtual QAbstractSeries * createSeries(ChartData const&) = 0;
    virtual QChart * createChart() = 0;
};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

void updateTemplate(ChartType);
void applyColorScheme(QChart * chart, ColorScheme scheme);

inline static const QVector<ChartType> gSupportedChartTypes {ChartType::Pie, ChartType::Bar, ChartType::Line};
inline static const QVector<ColorScheme> gSupportedColorSchemes {ColorScheme::Light, ColorScheme::Dark, ColorScheme::BlueCerulean};
