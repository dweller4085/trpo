#include "data.hh"

#include <memory>
#include "iocc.hh"

static std::shared_ptr<IDataReadingStrategy> strategyFor(DataFormat format) {
    switch (format) {
        case JSON: return std::make_shared<JSONStrategy>(); break;
        case CSV: return std::make_shared<CSVStrategy>(); break;
        case SQLITE: return std::make_shared<SQLiteStrategy>(); break;
        default: return std::make_shared<NullStrategy>(); break;
    }
}

void updateStrategy(QFileInfo const& info) {
    for (auto format: gSupportedDataFormats) {
        if (extension(format) == info.completeSuffix()) {
            gIoCContainer.registerService<IDataReadingStrategy>(strategyFor(format));
        }
    }
}

QString extension(DataFormat format) {
    QString ext; switch (format) {
        case JSON: ext = "json"; break;
        case CSV: ext = "csv"; break;
        case SQLITE: ext = "sqlite"; break;
        default: ext = ""; break;
    } return ext;
}
