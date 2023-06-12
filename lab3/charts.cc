#include "charts.hh"
#include "iocc.hh"

namespace {
    struct PieChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            return {};
        }

        virtual QChart * createChart(QAbstractSeries * series) override {
            return new QChart {};
        }
    };

    struct BarChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            //auto series = new QBarSeries {};
            //auto barset = new QBarSet {};

            return {};
        }

        virtual QChart * createChart(QAbstractSeries * series) override {
            return {};
        }
    };

    struct LineChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const& data) override {
            auto series = new QLineSeries {};
            /*
            for (auto point: data.points) {
                series->append({point.time, point.value});
            }
            */

            return series;
        }

        virtual QChart * createChart(QAbstractSeries * series) override {
            auto chart = new QChart {};
            chart->addSeries(series);
            chart->createDefaultAxes();
            return chart;
        }
    };

    struct NullChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            return {};
        }

        virtual QChart * createChart(QAbstractSeries * series) override {
            return new QChart {};
        }
    };

    std::shared_ptr<IChartTemplate> templateFor(ChartType type) {
        switch (type) {
            case ChartType::Pie: return std::make_shared<PieChart>(); break;
            case ChartType::Bar: return std::make_shared<BarChart>(); break;
            case ChartType::Line: return std::make_shared<LineChart>(); break;
            default: return std::make_shared<NullChart>(); break;
        }
    }
}

QChart * IChartTemplate::build(ChartData const& cd, ColorScheme cs) {
    auto series = this->createSeries(cd);
    if (!series) return nullptr;
    auto chart = this->createChart(series);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->legend()->hide();
    chart->setTitle(cd.chartTitle);

    applyColorScheme(chart, cs);
    return chart;
}

QString asString(ColorScheme scheme) {
    QString s; switch (scheme) {
        case ColorScheme::Light: s = "Light"; break;
        case ColorScheme::BlueCerulean: s = "Blue Cerulean"; break;
        case ColorScheme::BlackAndWhite: s = "Black&White"; break;
        default: s = ""; break;
    } return s;
}

QString asString(ChartType type) {
    QString s; switch (type) {
        case ChartType::Pie: s = "Pie"; break;
        case ChartType::Bar: s = "Bar"; break;
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
