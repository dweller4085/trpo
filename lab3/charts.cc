#include "charts.hh"
#include "iocc.hh"

#include <QDate>
#include <QDateTime>

namespace {
    struct PieChart: IChartTemplate {
        virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) override {
            auto series = new QPieSeries {};

            for (auto point: data.points) {
                auto ok = bool {true};
                auto value {point.value.toFloat(&ok)};

                if (ok) {
                    series->append(point.key, value);
                } else {
                    errMsg = "Pie chart only supports data of format (string, real).";
                    return false;
                }
            }

            chart->addSeries(series);
            chart->legend()->show();

            return true;
        }
    };


    struct ScatterChart: IChartTemplate {
        virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) override {
            auto series = new QScatterSeries {};
            series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
            series->setMarkerSize(20.0);

            for (auto point: data.points) {
                bool okx = true;
                bool oky = true;

                float x = point.key.toFloat(&okx);
                float y = point.value.toFloat(&oky);

                if (okx && oky) {
                    series->append({x, y});
                } else {
                    errMsg = "Scatter plot only supports data of format (real, real).";
                    return false;
                }
            }

            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->axes(Qt::Horizontal).first()->setTitleText(data.keyAxisTitle);
            chart->axes(Qt::Vertical).first()->setTitleText(data.valueAxisTitle);
            chart->legend()->hide();

            return true;
        }
    };


    struct LineChart: IChartTemplate {
        virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) override {
            auto series = new QLineSeries {};

            bool looksLikeADate = true;

            for (auto point: data.points) {
                bool okx = true;
                bool oky = true;

                float x, y;

                auto date = QDateTime {{QDate::fromString(point.key, "yyyy.MM")}};

                if (looksLikeADate && date.isValid()) {
                    x = (float) date.toMSecsSinceEpoch();
                } else {
                    x = point.key.toFloat(&okx);
                    looksLikeADate = false;
                }

                y = point.value.toFloat(&oky);

                if (okx && oky) {
                    series->append({x, y});
                } else {
                    errMsg = "Line chart only supports data of format (real, real), or (\"yyyy.mm\", real)";
                    return false;
                }
            }

            chart->addSeries(series);
            chart->legend()->hide();

            if (looksLikeADate) {
                auto dateTimeAxis = new QDateTimeAxis {};
                auto valueAxis = new QValueAxis {};

                dateTimeAxis->setFormat("yyyy.MM");
                //dateTimeAxis->setTickCount(data.points.length());
                dateTimeAxis->setTickCount(7);

                chart->addAxis(dateTimeAxis, Qt::AlignBottom);
                chart->addAxis(valueAxis, Qt::AlignLeft);

                series->attachAxis(dateTimeAxis);
                series->attachAxis(valueAxis);
            } else {
                chart->createDefaultAxes();
                chart->axes(Qt::Horizontal).first()->setTitleText(data.keyAxisTitle);
                chart->axes(Qt::Vertical).first()->setTitleText(data.valueAxisTitle);
            }

            return true;
        }
    };

    struct BarChart: IChartTemplate {
        virtual bool setupChart(QChart * chart, ChartData const& data, QString& errMsg) override {
            auto series = new QBarSeries {};

            for (auto point: data.points) {
                auto ok = bool {true};
                auto value {point.value.toFloat(&ok)};

                if (ok) {
                    auto barSet = new QBarSet {point.key};
                    barSet->append(value);
                    series->append(barSet);
                } else {
                    errMsg = "Bar chart only supports data of format (string, real).";
                    return false;
                }
            }

            auto valueAxis = new QValueAxis {};
            valueAxis->setTitleText(data.valueAxisTitle);

            chart->legend()->show();
            chart->addSeries(series);
            chart->addAxis(valueAxis, Qt::AlignLeft);

            series->attachAxis(valueAxis);

            return true;
        }
    };

    struct NullChart: IChartTemplate {
        virtual bool setupChart(QChart *, ChartData const&, QString&) override {
            return true;
        }
    };

    std::shared_ptr<IChartTemplate> templateFor(ChartType type) {
        switch (type) {
            case ChartType::Pie: return std::make_shared<PieChart>(); break;
            case ChartType::Scatter: return std::make_shared<ScatterChart>(); break;
            case ChartType::Line: return std::make_shared<LineChart>(); break;
            case ChartType::Bar: return std::make_shared<BarChart>(); break;
            default: return std::make_shared<NullChart>(); break;
        }
    }

    void clearChart(QChart * chart) {
        chart->removeAllSeries();
        for (auto axis: chart->axes()) {
            chart->removeAxis(axis);
        }
    }
}

bool IChartTemplate::setup(QChart * chart, ChartData const& data, ColorScheme colorScheme, QString& errMsg) {
    clearChart(chart);

    if (!this->setupChart(chart, data, errMsg)) return false;

    chart->setTitle(data.chartTitle);
    applyColorScheme(chart, colorScheme);

    return true;
}

QString asString(ColorScheme scheme) {
    QString s; switch (scheme) {
        case ColorScheme::Light: s = "Light"; break;
        case ColorScheme::Dark: s = "Dark"; break;
        case ColorScheme::BrownSand: s = "Brown Sand"; break;
        case ColorScheme::BlackAndWhite: s = "Black & White"; break;
        default: s = ""; break;
    } return s;
}

QString asString(ChartType type) {
    QString s; switch (type) {
        case ChartType::Pie: s = "Pie"; break;
        case ChartType::Scatter: s = "Scatter"; break;
        case ChartType::Line: s = "Line"; break;
        case ChartType::Bar: s = "Bar"; break;
        default: s = ""; break;
    } return s;
}

void updateTemplate(ChartType type) {
    gIoCContainer.registerService<IChartTemplate>(templateFor(type));
}

void applyColorScheme(QChart * chart, ColorScheme scheme) {
    switch (scheme) {
        case ColorScheme::Light: {
            chart->setTheme(QChart::ChartThemeLight);
            chart->setGraphicsEffect(nullptr);
        } break;
        case ColorScheme::Dark: {
            chart->setTheme(QChart::ChartThemeDark);
            chart->setGraphicsEffect(nullptr);
        } break;
        case ColorScheme::BrownSand: {
            chart->setTheme(QChart::ChartThemeBrownSand);
            chart->setGraphicsEffect(nullptr);
        } break;
        case ColorScheme::BlackAndWhite: {
            auto graphicsEffect = new QGraphicsColorizeEffect {};
            graphicsEffect->setColor(Qt::black);
            chart->setTheme(QChart::ChartThemeLight);
            chart->setGraphicsEffect(graphicsEffect);
        } break;
    }
}
