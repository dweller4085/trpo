#include <QFileInfo>
#include <Qdebug>
#include "filewatcher.hh"

FileWatcher::FileWatcher () : FileWatcher {nullptr} {}

FileWatcher::FileWatcher (QObject * parent) : QObject {parent}, timer {this} {
    QObject::connect (&self.timer, &QTimer::timeout, this, &FileWatcher::checkFiles);
    self.timer.setInterval (1000);
}

FileWatcher::FileWatcher (QVector<QString> const & files_to_watch) : FileWatcher {} {
    u32 filecount = files_to_watch.length();

    qInfo() << "A FileWatcher was created with" << filecount << "files to watch:\n";

    for (let const & filepath : files_to_watch) {
        QFileInfo const file_info {filepath};

        self.watched_files.append (File {
            filepath,
            (u64) file_info.size(),
            file_info.exists()
        });

        let const & file = self.watched_files.last();
        qInfo().nospace() << "[" << filecount-- << "] " << file.path << " Exists: " << file.exists << "; Size: " << file.size << "\n";
    }
}

FileWatcher::~FileWatcher () {
    self.stopWatch ();
}

void FileWatcher::startWatch (u32 interval_ms) {
    qInfo () << "Began watch with interval of" << interval_ms << "ms.\n";
    self.timer.setInterval (interval_ms);
    self.timer.start ();
}

void FileWatcher::stopWatch () {
    qInfo () << "Stopped watch.\n";
    self.timer.stop ();
}

void FileWatcher::checkFiles () {
    for (let & file : self.watched_files) {
        QFileInfo const file_info {file.path};
        let size_diff = file_info.size() - file.size;

        if (file.exists && !file_info.exists()) {
            emit FileWatcher::fileChanged (file_info.filePath(), FileWatcher::ChangeType::Deleted    , size_diff);
        } else if (!file.exists && file_info.exists()) {
            emit FileWatcher::fileChanged (file_info.filePath(), FileWatcher::ChangeType::Created    , size_diff);
        } else if (file.size != (u64) file_info.size()) {
            emit FileWatcher::fileChanged (file_info.filePath(), FileWatcher::ChangeType::SizeChanged, size_diff);
        }
        
        file.exists = file_info.exists ();
        file.size = file_info.size ();
    }
}
