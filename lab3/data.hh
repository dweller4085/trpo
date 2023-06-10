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

enum DataFormat { JSON, CSV, SQLITE };

struct IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) = 0;
    virtual ~IDataReadingStrategy() = default;
};



struct JSONStrategy: IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override;
};

struct CSVStrategy: IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override;
};

struct SQLiteStrategy: IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override;
};

struct NullStrategy: IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override;
};

void updateStrategy(QFileInfo const&);
QString extension(DataFormat format);

QVector<DataFormat> inline static const gSupportedDataFormats {DataFormat::JSON, DataFormat::CSV};
