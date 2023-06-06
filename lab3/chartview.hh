#ifndef CHARTVIEW_HH
#define CHARTVIEW_HH

#include <QWidget>
#include <QPushButton>
#include <QComboBox>

class ChartView: public QWidget { Q_OBJECT
public:
    explicit ChartView(QWidget * parent);

private:
    QComboBox * chartType;
    QComboBox * colorScheme;
    QPushButton * saveToPDF;
};

#endif // CHARTVIEW_HH
