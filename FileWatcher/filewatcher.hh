#ifndef FILEWATCHER_HH
#define FILEWATCHER_HH

#include <QObject>
#include <QVector>
#include <QString>
#include "common.hh"

class FileWatcher : QObject { Q_OBJECT
public:
    FileWatcher ();
    explicit FileWatcher (QObject *parent) {}
    explicit FileWatcher (QVector<QString> && files_to_watch) : files_to_watch {move (files_to_watch)} {}
    FileWatcher (FileWatcher && fw) : files_to_watch {move (fw.files_to_watch)} {}

    QVector<QString> files_to_watch;
};

#endif // FILEWATCHER_HH
