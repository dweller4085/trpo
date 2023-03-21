#include <QCoreApplication>
#include <Qdebug>
#include "filewatcher.hh"
#include "util.hh"
#include "common.hh"

fn main (i32 argc, char ** argv) -> i32 {
    QCoreApplication app {argc, argv};
    QTimer timer {};
    timer.setInterval(1000);

    FileWatcher file_watcher {};

    QObject::connect (&file_watcher, &FileWatcher::fileChanged, &report_file_change);
    QObject::connect (&timer, &QTimer::timeout, &file_watcher, &FileWatcher::checkFiles);
    QObject::connect (&file_watcher, &FileWatcher::logMessage, [&] (QString const & str) {qInfo().noquote().nospace() << str;});

    file_watcher.setWatchedFiles(read_args(argv));

    timer.start();
    return app.exec();
}
