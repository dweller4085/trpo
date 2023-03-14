#ifndef UTIL_HH
#define UTIL_HH
#include "filewatcher.hh"
#include "common.hh"

fn read_args (char const * const * argv) -> QVector<QString>;
fn report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff) -> nil;

#endif // UTIL_HH
