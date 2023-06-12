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
    void onDataReadFailed(QString const& errMsg);

private slots:
    void onChartTypeChanged(ChartType);
    void onColorSchemeChanged(ColorScheme);
    void onPbSaveToPDFPressed();

    void onCbChartTypeIndexChanged(int index);
    void onCbColorSchemeIndexChanged(int index);

private:
    enum class SharedView {Info, Chart};
    enum class MessageType {Info, Error};

    void drawChart();
    void displayMessage(QString const& msg, MessageType type);

    QChartView *  chartView;
    QComboBox *   cbChartType;
    QComboBox *   cbColorScheme;
    QPushButton * pbSaveToPDF;
    QLabel *      infoLabel;
    QStackedWidget * sharedView;

    ColorScheme colorScheme;
    ChartType chartType;

    ChartData const& data;
};
