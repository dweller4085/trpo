#ifndef COUNTER_HH
#define COUNTER_HH

#include <QObject>
#include <QString>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <MKB/aliases.h>

class Counter : public QLineEdit { Q_OBJECT
    s32 counter;
    s32 tickInterval;

public:
    Counter(s32 counter, s32 tickInterval, QWidget * parent);
    Counter(QWidget * parent): Counter {0, 1, parent} {}
    Counter(): Counter {nullptr} {}

signals:
    void tick();

public slots:
    void increment();
};

#endif // COUNTER_HH
