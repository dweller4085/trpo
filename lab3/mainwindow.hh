#pragma once

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QFileInfo>

#include "fileview.hh"
#include "chartview.hh"
#include "data.hh"

class MainWindow: public QMainWindow { Q_OBJECT
public:
    MainWindow();

signals:
    void dataChanged();
    void dataReadFailed(QString const&);

public slots:
    void onFileSelected(QFileInfo const&);

private:
    FileView * fileView;
    ChartView * chartView;
    ChartData data;
};
