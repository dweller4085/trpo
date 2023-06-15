#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum class ColorScheme { Light, Dark, BrownSand, BlackAndWhite, __count };
enum class ChartType { Line, Pie, Bar, __count };

struct IChartTemplate {
    bool setup(QChart * chart, ChartData const& data, ColorScheme colorScheme, QString& errMsg);

protected:
    virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) = 0;
};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

void updateTemplate(ChartType);
void applyColorScheme(QChart * chart, ColorScheme scheme);
