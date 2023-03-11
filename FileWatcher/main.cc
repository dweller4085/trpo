#include <QCoreApplication>
#include <cstdio>
#include "common.hh"
#include "filewatcher.hh"
#include "util.hh"

fn main (i32 argc, char ** argv) -> i32 {
    QCoreApplication app {argc, argv};

    let file_names = read_args (argv);
    let file_watcher = FileWatcher {move (file_names)};


    ret app.exec();
}
