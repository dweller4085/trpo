#include <QFileInfo>
#include <Qdebug>
#include "filewatcher.hh"

FileWatcher::FileWatcher () : FileWatcher {nullptr} {}

FileWatcher::FileWatcher (QObject * parent) : QObject {parent}, watched_files {} {}

FileWatcher & FileWatcher::instance () {
    static FileWatcher instance {};
    return instance;
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

QList<QString> FileWatcher::getWatchedFiles () const {
    let list = QList<QString> {};

    for (auto const & file : self.watched_files) {
        list.push_back (file.path);
    }

    return list;
}

void FileWatcher::addFile (QString filename) {
    let const file_info = QFileInfo {filename};
    let file = File {
        file_info.filePath(),
        (u64) file_info.size(),
        file_info.exists()
    };

    let message = QString {} + "Added a file to watch: \"" + file.path + "\" " + "[" + QString::number(file.size) + "] " + (file.exists ? "Exists." : "Does not exist.") + "\n";

    self.watched_files.push_back(move(file));

    emit FileWatcher::logMessage(move(message));
}

void FileWatcher::setWatchedFiles (QList<QString> files_to_watch) {
    let message = QString {} + (self.watched_files.isEmpty() ? "Set" : "Reset") + " to watch " + QString::number(files_to_watch.length()) + " files.";

    self.watched_files.clear();

    let i = 0;
    for (auto const & filepath : files_to_watch) {
        QFileInfo const file_info {filepath};

        let file = File {
            file_info.filePath(),
            (u64) file_info.size(),
            file_info.exists()
        };

        message += "\n" + QString::number(++i) + ". " + file.path + " [" + QString::number(file.size) + "] " + (file.exists ? "Exists." : "Does not exist.");

        self.watched_files.append (move (file));
    }

    emit FileWatcher::logMessage(move(message + "\n"));
}
