#include <QFileInfo>
#include <Qdebug>
#include "filewatcher.hh"

FileWatcher::FileWatcher () : FileWatcher {nullptr} {}

FileWatcher::FileWatcher (QObject * parent) : QObject {parent} {}

FileWatcher::FileWatcher (QVector<QString> const & files_to_watch) : FileWatcher {} {
    qInfo() << "A FileWatcher was created with" << files_to_watch.length() << "files to watch:";

    let i = 0;
    for (let const & filepath : files_to_watch) {
        QFileInfo const file_info {filepath};

        let file = File {
            file_info.filePath(),
            (u64) file_info.size(),
            file_info.exists()
        };

        qInfo().nospace() << "[" << ++i << "] " << file.path << " Exists? " << file.exists << "; Size: " << file.size;

        self.watched_files.append (move (file));
    }
}

void FileWatcher::checkFiles () {
    for (let & file : self.watched_files) {
        QFileInfo const file_info {file.path};
        let change_type = FileWatcher::ChangeType::Unchanged;

        if (file.exists && !file_info.exists()) {
            change_type = FileWatcher::ChangeType::Deleted;
        } else if (!file.exists && file_info.exists()) {
            change_type = FileWatcher::ChangeType::Created;
        } else if (file.size != (u64) file_info.size()) {
            change_type = FileWatcher::ChangeType::SizeChanged;
        }

        if (change_type != FileWatcher::ChangeType::Unchanged) {
            emit FileWatcher::fileChanged (file.path, change_type, file_info.size() - file.size);
            file.exists = file_info.exists();
            file.size = file_info.size();
        }
    }
}
