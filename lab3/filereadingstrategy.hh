#ifndef FILEREADINGSTRATEGY_HH
#define FILEREADINGSTRATEGY_HH

#include "common.hh"
#include <QFileInfo>

void updateStrategy(QFileInfo const&);

struct IFileReadingStrategy {
    virtual bool read(QString const& path, ChartData& data) = 0;
    virtual ~IFileReadingStrategy() = default;
};

struct JSONStrategy: IFileReadingStrategy {};

struct SQLiteStrategy: IFileReadingStrategy {};

struct NullStrategy: IFileReadingStrategy {};

#endif // FILEREADINGSTRATEGY_HH
