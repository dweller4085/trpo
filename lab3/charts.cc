#include "charts.hh"

namespace {
    struct BarChart: IChartTemplate {};
    struct PieChart: IChartTemplate {};
    struct LineChart: IChartTemplate {};
    struct NullChart: IChartTemplate {};
}

QChart * IChartTemplate::operator () (ChartData const& cd, ColorScheme const& cs) {
    auto series = this->generateSeries(cd);
    auto chart = this->generateChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    // set color scheme ...
    return chart;
}

QString asString(ColorScheme scheme) {
    QString s; switch (scheme) {
        case ColorScheme::Light: s = "Light"; break;
        case ColorScheme::BW: s = "BW"; break;
        case ColorScheme::BlueCerulean: s = "Blue Cerulean"; break;
        default: s = ""; break;
    } return s;
}

QString asString(ChartType type) {
    QString s; switch (type) {
        case ChartType::PieChart: s = "Pie"; break;
        case ChartType::BarChart: s = "Bar"; break;
        case ChartType::LineChart: s = "Line"; break;
        default: s = ""; break;
    } return s;
}
