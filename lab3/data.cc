#include "data.hh"

#include <QFile>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonDocument>

#include <memory>
#include "iocc.hh"

namespace {
    struct JSONStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            errorMsg = "Failed to parse this JSON file. Ask the dev what the format should be.";

            data.points.clear();

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
            errorMsg = "Could not read the CSV file.";

            data.points.clear();

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
            errorMsg = "SQLite file format is not supported.";
            return false;
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
