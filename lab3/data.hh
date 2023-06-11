#pragma once

#include <QFileInfo>
#include <QString>
#include <QVector>

struct ChartData {
    struct Point {
        float time;
        float value;
        //QString category;
    };

    QVector<Point> points;
};

enum class DataFormat { JSON, CSV, SQLITE };

struct IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) = 0;
    virtual ~IDataReadingStrategy() = default;
};

void updateStrategy(QFileInfo const&);
QString extension(DataFormat format);

QVector<DataFormat> inline static const gSupportedDataFormats {DataFormat::JSON, DataFormat::CSV};
