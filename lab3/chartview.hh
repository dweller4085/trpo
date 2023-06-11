#pragma once

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFileInfo>
#include <QWidget>
#include <QLabel>

#include <memory>

#include "charts.hh"

class ChartView: public QWidget { Q_OBJECT
public:
    ChartView(QWidget * parent, ChartData const& data);

public slots:
    void onDataChanged();
    void onDataInvalidated(QString const&);

private slots:
    void onChartTypeChanged(ChartType);
    void onColorSchemeChanged(ColorScheme);
    void onPbSaveToPDFPressed();

private:
    void drawChart();

    QChartView *  chartView;
    QComboBox *   cbChartType;
    QComboBox *   cbColorScheme;
    QPushButton * pbSaveToPDF;
    QLabel *      infoLabel;
    QStackedWidget * sharedView;

    ColorScheme colorScheme;
    ChartType chartType;

    ChartData const& data;

    enum {
        Chart,
        Info,
    };
};
