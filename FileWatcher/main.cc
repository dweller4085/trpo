#include <QCoreApplication>
#include <Qdebug>
#include <QTimer>
#include "filewatcher.hh"
#include "util.hh"
#include "common.hh"

fn main (i32 argc, char ** argv) -> i32 {
    QCoreApplication app {argc, argv};
    QTimer timer {};
    timer.setInterval(1000);

    let& file_watcher = FileWatcher::instance();

    QObject::connect (&file_watcher, &FileWatcher::fileChanged, &report_file_change);
    QObject::connect (&timer, &QTimer::timeout, &file_watcher, &FileWatcher::checkFiles);
    QObject::connect (&file_watcher, &FileWatcher::logMessage, [&] (QString str) {qInfo().noquote().nospace() << str;});

    file_watcher.setWatchedFiles(read_args(argv));
    file_watcher.addFile(QString {"C:\\lib\\MKB\\include\\MKB\\aliases.h"});
    file_watcher.setWatchedFiles({});

    timer.start();
    return app.exec();
}
