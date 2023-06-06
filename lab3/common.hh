#ifndef COMMON_HH
#define COMMON_HH

#include <QVector>
#include <QString>

struct ChartData {
    struct Point {
        float t;
        float v;
    };

    QVector<Point> points;
};

struct ColorScheme {
    enum {
        Light,
        Dark,
        BlueCerulean,
    } scheme;

    explicit operator QString() const {
        QString s;

        switch (scheme) {
            case Light:
                s = "Light";
            break;
            case Dark:
                s = "Dark";
            break;
            case BlueCerulean:
                s = "Blue Cerulean";
            break;
        }

        return s;
    }
};

struct ChartType {
    enum {
        Pie,
        Bar,
        Line,
    } type;

    explicit operator QString() const {
        QString s;

        switch (type) {
            case Pie:
                s = "Pie";
            break;
            case Bar:
                s = "Bar";
            break;
            case Line:
                s = "Line";
            break;
        }

        return s;
    }
};

struct DataFormat {
    enum {
        JSON,
        CSV
    } format;

    QString asExtension() const {
        QString ext;

        switch (format) {
            case JSON:
                ext = "*.json";
            break;
            case CSV:
                ext = "*.csv";
            break;
        }

        return ext;
    }
};

QVector<DataFormat> static const gSupportedDataFormats {{DataFormat::JSON}, {DataFormat::CSV}};
QVector<ChartType> static const gSupportedChartTypes {{ChartType::Pie}, {ChartType::Bar}, {ChartType::Line}};
QVector<ColorScheme> static const gSupportedColorSchemes {{ColorScheme::Light}, {ColorScheme::Dark}, {ColorScheme::BlueCerulean}};

#endif // COMMON_HH
