#ifndef UTIL_HH
#define UTIL_HH
#include <QString>
#include "filewatcher.hh"
#include "common.hh"

fn read_args (char const * const * argv) -> QList<QString>;
fn report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff) -> void;

#endif // UTIL_HH
