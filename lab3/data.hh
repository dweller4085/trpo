#pragma once

#include <QFileInfo>
#include <QString>
#include <QVector>

struct ChartData {
    struct Point {
        QString key;
        QString value;
    };

    QString keyAxisTitle;
    QString valueAxisTitle;
    QString chartTitle;
    QVector<Point> points;
};

enum class DataFormat { JSON, CSV, SQLITE };

struct IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) = 0;
    virtual ~IDataReadingStrategy() = default;
};

void updateStrategy(QFileInfo const& info);
QString extension(DataFormat format);

inline static const QVector<DataFormat> gSupportedDataFormats {DataFormat::JSON, DataFormat::CSV};
