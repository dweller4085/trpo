#ifndef FILEREADINGSTRATEGY_HH
#define FILEREADINGSTRATEGY_HH

#include "common.hh"

struct IFileReadingStrategy {
    virtual ChartData read(QString const& path, bool& success) = 0;
    virtual ~IFileReadingStrategy() = default;
};

struct JSON: IFileReadingStrategy {};

struct SQLite: IFileReadingStrategy {};

#endif // FILEREADINGSTRATEGY_HH
