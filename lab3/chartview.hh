#pragma once

#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFileInfo>
#include <QWidget>
#include <QLabel>

#include "charts.hh"

class ChartView: public QWidget { Q_OBJECT
public:
    explicit ChartView(QWidget * parent);

public slots:
    void onDataChanged(ChartData const&);
    void onDataInvalidated(QFileInfo const&);

private slots:
    //void onChartTypeChanged(ChartType);
    //void onColorSchemeChanged(ColorScheme);
    //void onPbSaveToPDFPressed();

private:
    QChartView *  chartView;
    QComboBox *   cbChartType;
    QComboBox *   cbColorScheme;
    QPushButton * pbSaveToPDF;
    QLabel * infoLabel;
    QVBoxLayout * layout;

    ColorScheme colorScheme;
    ChartType chartType;
};
