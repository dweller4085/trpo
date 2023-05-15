#ifndef COUNTER_HH
#define COUNTER_HH

#include <QObject>
#include <QString>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <MKB/aliases.h>

class Counter : public QLineEdit { Q_OBJECT
    s32 i {0};

public:
    Counter(QWidget * parent);
    Counter(): Counter {nullptr} {}

signals:
    void tick_signal();

public slots:
    void add_one() {
        QString str=text();
        int r=str.toInt();
        if (r!=0 && r%5 ==0) emit tick_signal();
        r++;
        str.setNum(r);
        setText(str);
    }
};

#endif // COUNTER_HH
