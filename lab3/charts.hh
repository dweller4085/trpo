#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum class ColorScheme { Light, BlueCerulean, BlackAndWhite };
enum class ChartType { Line, Pie, Scatter };

struct IChartTemplate {
    bool setup(QChart * chart, ChartData const& data, ColorScheme colorScheme, QString& errMsg);

protected:
    virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) = 0;
};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

void updateTemplate(ChartType);
void applyColorScheme(QChart * chart, ColorScheme scheme);

inline static const QVector<ChartType> gSupportedChartTypes {ChartType::Line, ChartType::Pie, ChartType::Scatter};
inline static const QVector<ColorScheme> gSupportedColorSchemes {ColorScheme::Light, ColorScheme::BlueCerulean, ColorScheme::BlackAndWhite};
