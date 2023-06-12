#include "charts.hh"
#include "iocc.hh"

namespace {
    struct PieChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            return {};
        }

        virtual QChart * createChart() override {
            return {};
        }
    };

    struct BarChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            return {};
        }

        virtual QChart * createChart() override {
            return {};
        }
    };

    struct LineChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const& data) override {
            auto lineSeries = new QLineSeries {};

            for (auto point: data.points) {
                lineSeries->append({point.time, point.value});
            }

            return lineSeries;
        }

        virtual QChart * createChart() override {
            return new QChart {};
        }
    };

    struct NullChart: IChartTemplate {
        virtual QAbstractSeries * createSeries(ChartData const&) override {
            return {};
        }

        virtual QChart * createChart() override {
            return {};
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

QChart * IChartTemplate::build(ChartData const& cd, ColorScheme const& cs) {
    auto series = this->createSeries(cd);
    auto chart = this->createChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    applyColorScheme(chart, cs);
    return chart;
}

QString asString(ColorScheme scheme) {
    QString s; switch (scheme) {
        case ColorScheme::Light: s = "Light"; break;
        case ColorScheme::Dark: s = "Dark"; break;
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

}
