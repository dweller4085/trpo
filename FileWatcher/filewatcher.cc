#include <QFileInfo>
#include <Qdebug>
#include "filewatcher.hh"

FileWatcher::FileWatcher () : FileWatcher {nullptr} {}

FileWatcher::FileWatcher (QObject * parent) : QObject {parent}, watched_files {} {}

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

QList<QString> FileWatcher::getWatchedFiles () const {
    let list = QList<QString> {};

    for (auto const & file : self.watched_files) {
        list.push_back (file.path);
    }

    return list;
}

void FileWatcher::setWatchedFiles (QList<QString> const & files_to_watch) {
    let message = QString {} + (self.watched_files.isEmpty() ? "Set to " : "Reset to ") + QString::number(files_to_watch.length()) + " files to watch.";

    self.watched_files.clear();

    let i = 0;
    for (auto const & filepath : files_to_watch) {
        QFileInfo const file_info {filepath};

        let file = File {
            file_info.filePath(),
            (u64) file_info.size(),
            file_info.exists()
        };

        message += "\n[" + QString::number(++i) + "] " + file.path + " [" + QString::number(file.size) + "] " + (file.exists ? "Exists." : "Does not exist.");

        self.watched_files.append (move (file));
    }

    emit FileWatcher::logMessage(message + "\n");
}
