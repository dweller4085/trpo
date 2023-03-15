#include <QCoreApplication>
#include <cstdio>
#include "filewatcher.hh"
#include "util.hh"
#include "common.hh"

fn main (i32 argc, char ** argv) -> i32 {
    QCoreApplication app {argc, argv};
    QTimer timer;
    timer.setInterval(1000);

    FileWatcher file_watcher {read_args (argv)};

    QObject::connect (&file_watcher, &FileWatcher::fileChanged, &report_file_change);
    QObject::connect (&timer, &QTimer::timeout, [&] {file_watcher.checkFiles();});

    timer.start();

    return app.exec();
}
