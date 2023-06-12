#pragma once

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QtCharts>
#include <QtCharts/QChart>

#include "data.hh"

enum class ColorScheme { Light, BlueCerulean, BlackAndWhite };
enum class ChartType { Line, Pie, Bar };

struct IChartTemplate {
    QChart * build (ChartData const& cd, ColorScheme cs, QString& errMsg);

protected:
    virtual QAbstractSeries * createSeries(ChartData const& data, QString& errMsg) = 0;
    virtual QChart * createChart(ChartData const& data, QAbstractSeries * series) = 0;
};

QString asString(ColorScheme scheme);
QString asString(ChartType type);

void updateTemplate(ChartType);
void applyColorScheme(QChart * chart, ColorScheme scheme);

inline static const QVector<ChartType> gSupportedChartTypes {ChartType::Line, ChartType::Pie, ChartType::Bar};
inline static const QVector<ColorScheme> gSupportedColorSchemes {ColorScheme::Light, ColorScheme::BlueCerulean, ColorScheme::BlackAndWhite};
