#ifndef CHARTVIEW_HH
#define CHARTVIEW_HH

#include "common.hh"
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QFileInfo>


class ChartView: public QWidget { Q_OBJECT
public:
    explicit ChartView(QWidget * parent);

public slots:
    void onDataChanged(ChartData const&);
    void onDataInvalidated(QFileInfo const&);

private slots:
    //void onChartTypeChanged(ChartType);
    //void onColorSchemeChanged(ColorScheme);

private:
    QChartView *  chartView;
    QComboBox *   cbChartType;
    QComboBox *   cbColorScheme;
    QPushButton * pbSaveToPDF;
    QLabel * infoLabel;
    QVBoxLayout * layout;

    ColorScheme colorScheme;
    ChartType type;
};

#endif // CHARTVIEW_HH
