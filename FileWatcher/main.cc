#include <QCoreApplication>
#include <cstdio>
#include "filewatcher.hh"
#include "util.hh"
#include "common.hh"

fn main (i32 argc, char ** argv) -> i32 {
    QCoreApplication app {argc, argv};

    let file_names = read_args (argv);
    FileWatcher file_watcher {move (file_names)};
    QObject::connect(&file_watcher, &FileWatcher::fileChanged, &report_file_change);

    file_watcher.startWatch (1000);

    ret app.exec();
}
