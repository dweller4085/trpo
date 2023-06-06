#ifndef CHARTVIEW_HH
#define CHARTVIEW_HH

#include "common.hh"
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>


class ChartView: public QWidget { Q_OBJECT
public:
    explicit ChartView(QWidget * parent);

public slots:
    void onDataChanged(ChartData const&);

private slots:
    void onChartTypeChanged(ChartType);
    void onColorSchemeChanged(ColorScheme);

private:
    QChartView *  chartView;
    QComboBox *   cbChartType;
    QComboBox *   cbColorScheme;
    QPushButton * pbSaveToPDF;

    ColorScheme colorScheme;
};

#endif // CHARTVIEW_HH
