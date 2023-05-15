#include "counter.hh"

Counter::Counter(s32 counter, s32 tickInterval, QWidget * parent):
    QLineEdit {"0", parent},
    counter {counter},
    tickInterval {tickInterval}
{}

void Counter::increment() {
    counter += 1;
    if (counter % tickInterval == 0) emit Counter::tick();
    this->setText(QString::number(counter));
}
