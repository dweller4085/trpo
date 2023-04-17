#ifndef UTIL_HH
#define UTIL_HH
#include <QString>
#include "filewatcher.hh"
#include "common.hh"

QList<QString> read_args (char const * const * argv);
void report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff);

#endif // UTIL_HH
