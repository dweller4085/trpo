#include "charts.hh"

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
