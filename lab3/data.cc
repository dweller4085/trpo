#include "data.hh"

#include <QFile>
#include <QDateTime>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonDocument>

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

#include <memory>
#include "iocc.hh"

namespace {
    struct JSONStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            errorMsg = "Failed to parse this JSON file. Ask the dev what the format should be.";

            data = ChartData {};

            auto file = QFile {path};
            if (!file.exists() || !file.open(QIODevice::ReadOnly)) return false;
            auto rawData = file.readAll();
            file.close();

            auto jsonDocument = QJsonDocument::fromJson(rawData);
            if (!jsonDocument.isObject()) return false;

            auto const jsonObject = jsonDocument.object();

            if (!(  jsonObject.contains("chartTitle") &&
                    jsonObject.contains("keyAxisTitle") &&
                    jsonObject.contains("valueAxisTitle") &&
                    jsonObject.contains("data"))
            ) return false;

            data.chartTitle = jsonObject.value("chartTitle").toString();
            data.keyAxisTitle = jsonObject.value("keyAxisTitle").toString();
            data.valueAxisTitle = jsonObject.value("valueAxisTitle").toString();

            auto jsonData = jsonObject.value("data");
            if (!jsonData.isArray()) return false;

            for (auto const item: jsonData.toArray()) {
                if (!item.isArray()) return false;
                auto pair = item.toArray();

                if (pair.size() != 2) return false;

                auto key = pair.at(0).toString();
                auto value = pair.at(1).toString();
                data.points.push_back({key, value});
            }

            return true;
        }
    };

    struct CSVStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            errorMsg = "Could not read this CSV file.";

            data = ChartData {};

            auto file = QFile {path};
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            auto stream = QTextStream {&file};

            auto line = stream.readLine().split(',');
            if (line.isEmpty()) return false;

            data.chartTitle = line.first();

            line = stream.readLine().split(',');
            if (line.size() != 2) return false;

            data.keyAxisTitle = line.first();
            data.valueAxisTitle = line.last();

            while (!stream.atEnd()) {
                auto pair = stream.readLine().split(',');
                if (pair.size() != 2) return false;

                data.points.push_back({pair.first(), pair.last()});
            }

            return true;
        }
    };

    struct SQLiteStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            errorMsg = "Something went wrong while trying to read this SQLite file.";

            data = ChartData {};

            auto static db = QSqlDatabase::addDatabase("QSQLITE");

            if (!QFile::exists(path)) return false;

            db.setDatabaseName(path);

            if (!db.open()) return false;

            auto table = db.tables().first();

            data.chartTitle = table;

            auto query = QSqlQuery {"select * from " + table /* + " order by 1 asc"*/};
            //query.exec();

            if (!query.next()) { db.close(); return false; }
            auto prevDate = query.value(0).toString().split(' ').first().split('.');
            auto prevValue = query.value(1).toFloat();

            //auto prevDay = prevDate.at(0).toInt();
            auto prevMonth = prevDate.at(1).toInt();
            auto prevYear = prevDate.at(2).toInt();

            float averageValue = prevValue;
            int n = 1;

            while (query.next()) {
                auto currDate = query.value(0).toString().split(' ').first().split('.');
                auto currValue = query.value(1).toFloat();

                //auto currDay = currDate.at(0).toInt();
                auto currMonth = currDate.at(1).toInt();
                auto currYear = currDate.at(2).toInt();

                if (currYear == prevYear && currMonth == prevMonth) {
                    n += 1;
                    averageValue += currValue;
                }

                else {
                    averageValue /= (float) n;
                    auto strMonth = QString::number(prevMonth);

                    if (prevMonth < 10) {
                        strMonth = QString {"0"} + strMonth;
                    }

                    data.points.push_back({QString::number(prevYear) + "." + strMonth, QString::number(averageValue)});

                    prevYear = currYear;
                    prevMonth = currMonth;
                    //prevValue = currValue;

                    averageValue = currValue;
                    n = 1;
                }
            }

            db.close();
            return true;
        }
    };

    struct NullStrategy: IDataReadingStrategy {
        virtual bool read(QString const&, ChartData&, QString&) override {
            return false;
        }
    };

    std::shared_ptr<IDataReadingStrategy> strategyFor(DataFormat format) {
        switch (format) {
            case DataFormat::JSON: return std::make_shared<JSONStrategy>(); break;
            case DataFormat::CSV: return std::make_shared<CSVStrategy>(); break;
            case DataFormat::SQLITE: return std::make_shared<SQLiteStrategy>(); break;
            default: return std::make_shared<NullStrategy>(); break;
        }
    }
}

QString extension(DataFormat format) {
    QString ext; switch (format) {
        case DataFormat::JSON: ext = "json"; break;
        case DataFormat::CSV: ext = "csv"; break;
        case DataFormat::SQLITE: ext = "sqlite"; break;
        default: ext = ""; break;
    } return ext;
}

void updateStrategy(QFileInfo const& info) {
    for (auto format: gSupportedDataFormats) {
        if (extension(format) == info.completeSuffix()) {
            gIoCContainer.registerService<IDataReadingStrategy>(strategyFor(format));
        }
    }
}
