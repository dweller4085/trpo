#include "charts.hh"

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
        case Light: s = "Light"; break;
        case BW: s = "BW"; break;
        case BlueCerulean: s = "Blue Cerulean"; break;
        default: s = ""; break;
    } return s;
}

QString asString(ChartType type) {
    QString s; switch (type) {
        case PieChart: s = "Pie"; break;
        case BarChart: s = "Bar"; break;
        case LineChart: s = "Line"; break;
        default: s = ""; break;
    } return s;
}
