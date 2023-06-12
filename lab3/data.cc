#include "data.hh"

#include <memory>
#include "iocc.hh"

namespace {
    struct JSONStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            return {};
        }
    };

    struct CSVStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            // for debug purposes
            data.points = {{1, 1}, {2, 2}, {3, 3}, {4, 2}};
            return true;
        }
    };

    struct SQLiteStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
            return {};
        }
    };

    struct NullStrategy: IDataReadingStrategy {
        virtual bool read(QString const& path, ChartData& data, QString& errorMsg) override {
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
