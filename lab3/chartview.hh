#ifndef CHARTVIEW_HH
#define CHARTVIEW_HH

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>

class ChartView: public QWidget { Q_OBJECT
public:
    explicit ChartView(QWidget * parent);

private:
    QChartView * chartView;
    QComboBox * chartType;
    QComboBox * colorScheme;
    QPushButton * saveToPDF;
};

#endif // CHARTVIEW_HH
