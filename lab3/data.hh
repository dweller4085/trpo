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

struct DataFormat {
    enum { JSON, CSV, } format;

    QString asExtension() const {
        QString ext; switch (format) {
            case JSON: ext = "json"; break;
            case CSV: ext = "csv"; break;
            default: ext = ""; break;
        } return ext;
    }
};

struct IDataReadingStrategy {
    virtual bool read(QString const& path, ChartData& data, QString& errorMsg) = 0;
    virtual ~IDataReadingStrategy() = default;
};

struct JSONStrategy: IDataReadingStrategy {};
struct SQLiteStrategy: IDataReadingStrategy {};
struct NullStrategy: IDataReadingStrategy {};

void updateStrategy(QFileInfo const&);

QVector<DataFormat> inline static const gSupportedDataFormats {{DataFormat::JSON}, {DataFormat::CSV}};
