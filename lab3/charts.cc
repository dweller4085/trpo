#include "charts.hh"
#include "iocc.hh"

namespace {
    struct PieChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const& data, QString& errMsg) override {
            auto series = new QPieSeries {};

            for (auto point: data.points) {
                auto ok = bool {true};
                auto value {point.value.toFloat(&ok)};

                if (ok) {
                    series->append(point.key, value);
                } else {
                    errMsg = "Pie chart only supports data of format (string, real).";
                    return nullptr;
                }
            }

            return series;
        }

        virtual QChart * createChart(ChartData const& data, QAbstractSeries * series) override {
            auto chart = new QChart {};
            chart->addSeries(series);
            chart->legend()->show();

            return chart;
        }
    };

    struct ScatterChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const& data, QString& errMsg) override {
            // this was going to be a barset, but started to get way too complicated
            /*
            auto barset = new QBarSet {{}};
            auto series = new QBarSeries {};

            int const segmentCnt = std::min(data.points.length(), 18);

            // check that we have only reals in (K, V) pairs; and that keys are ordered asc.
            float prevKey = -10e6;
            for (auto point: data.points) {
                bool okK = true;
                bool okV = true;
                float currKey = point.key.toFloat(&okK);
                point.value.toFloat(&okV);
                if (!okK || !okV) {
                    errMsg = "Bar chart only supports data of format (real, real).";
                    return nullptr;
                } else if (currKey < prevKey) {
                    errMsg = "Bar chart only supports real key-value pairs, sorted by key ascending.";
                    return nullptr;
                }
            }

            float minX = data.points.first().key.toFloat(&oka);
            float maxX = data.points.last().key.toFloat(&okb);

            int j = 0;
            for (int i = 0; i < segmentCnt; i += 1) {
                int k = 0;

            }
            */

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
                    return nullptr;
                }
            }


            return series;
        }

        virtual QChart * createChart(ChartData const& data, QAbstractSeries * series) override {
            auto chart = new QChart {};
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->axes(Qt::Horizontal).first()->setTitleText(data.keyAxisTitle);
            chart->axes(Qt::Vertical).first()->setTitleText(data.valueAxisTitle);
            chart->legend()->hide();

            return chart;
        }
    };

    struct LineChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const& data, QString& errMsg) override {
            auto series = new QLineSeries {};

            for (auto point: data.points) {
                bool okx = true;
                bool oky = true;

                float x = point.key.toFloat(&okx);
                float y = point.value.toFloat(&oky);

                if (okx && oky) {
                    series->append({x, y});
                } else {
                    errMsg = "Line chart only supports data of format (real, real).";
                    return nullptr;
                }
            }

            return series;
        }

        virtual QChart * createChart(ChartData const& data, QAbstractSeries * series) override {
            auto chart = new QChart {};
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->axes(Qt::Horizontal).first()->setTitleText(data.keyAxisTitle);
            chart->axes(Qt::Vertical).first()->setTitleText(data.valueAxisTitle);
            chart->legend()->hide();
            return chart;
        }
    };

    struct NullChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&, QString&) override {
            return {};
        }

        virtual QChart * createChart(ChartData const&, QAbstractSeries *) override {
            return {};
        }
    };

    std::shared_ptr<IChartTemplate> templateFor(ChartType type) {
        switch (type) {
            case ChartType::Pie: return std::make_shared<PieChart>(); break;
            case ChartType::Scatter: return std::make_shared<ScatterChart>(); break;
            case ChartType::Line: return std::make_shared<LineChart>(); break;
            default: return std::make_shared<NullChart>(); break;
        }
    }
}

QChart * IChartTemplate::build(ChartData const& cd, ColorScheme cs, QString& errMsg) {
    auto series = this->createSeries(cd, errMsg);
    if (!series) return nullptr;

    auto chart = this->createChart(cd, series);

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->setTitle(cd.chartTitle);

    applyColorScheme(chart, cs);

    return chart;
}

QString asString(ColorScheme scheme) {
    QString s; switch (scheme) {
        case ColorScheme::Light: s = "Light"; break;
        case ColorScheme::BlueCerulean: s = "Blue Cerulean"; break;
        case ColorScheme::BlackAndWhite: s = "Black & White"; break;
        default: s = ""; break;
    } return s;
}

QString asString(ChartType type) {
    QString s; switch (type) {
        case ChartType::Pie: s = "Pie"; break;
        case ChartType::Scatter: s = "Scatter"; break;
        case ChartType::Line: s = "Line"; break;
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
        case ColorScheme::BlueCerulean: {
            chart->setTheme(QChart::ChartThemeBlueCerulean);
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
