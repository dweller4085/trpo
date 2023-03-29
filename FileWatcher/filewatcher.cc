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
    for (let kv = self.watched_files.begin(); kv != self.watched_files.end(); kv++) {
        QFileInfo const file_info {kv.key()};
        let change_type = FileWatcher::ChangeType::Unchanged;

        if (kv.value().exists && !file_info.exists()) {
            change_type = FileWatcher::ChangeType::Deleted;
        } else if (!kv.value().exists && file_info.exists()) {
            change_type = FileWatcher::ChangeType::Created;
        } else if (kv.value().size != (u64) file_info.size()) {
            change_type = FileWatcher::ChangeType::SizeChanged;
        }

        if (change_type != FileWatcher::ChangeType::Unchanged) {
            emit FileWatcher::fileChanged (kv.key(), change_type, file_info.size() - kv.value().size);
            kv.value().exists = file_info.exists();
            kv.value().size = file_info.size();
        }
    }
}

QList<QString> FileWatcher::getWatchedFiles () const {
    let list = QList<QString> {};

    for (auto i = self.watched_files.keyBegin(); i != self.watched_files.keyEnd(); i++) {
        list.push_back (*i);
    }

    return list;
}

void FileWatcher::addFile (QString filename) {
    let const file_info = QFileInfo {filename};

    if (watched_files.contains(file_info.absoluteFilePath())) {
        emit FileWatcher::logMessage(QString {} + file_info.absoluteFilePath() + " is already being watched.\n");
        return;
    }

    let file_status = FileStatus__ {
        (u64) file_info.size(),
        file_info.exists()
    };

    let message = QString {} + "Added a file to watch: \"" + file_info.absoluteFilePath() + "\" " + "[" + QString::number(file_status.size) + "] " + (file_status.exists ? "Exists." : "Does not exist.") + "\n";

    self.watched_files.insert(file_info.absoluteFilePath(), file_status);

    emit FileWatcher::logMessage(move(message));
}

void FileWatcher::setWatchedFiles (QList<QString> files_to_watch) {
    let message = QString {} + (self.watched_files.isEmpty() ? "Set" : "Reset") + " to watch " + QString::number(files_to_watch.length()) + " files.";

    self.watched_files.clear();

    let i = 0;
    for (auto const & filepath : files_to_watch) {
        QFileInfo const file_info {filepath};

        if (!watched_files.contains(file_info.absoluteFilePath())) {
            let file_status = FileStatus__ {
                (u64) file_info.size(),
                file_info.exists()
            };
            message += "\n" + QString::number(++i) + ". " + file_info.absoluteFilePath() + " [" + QString::number(file_status.size) + "] " + (file_status.exists ? "Exists." : "Does not exist.");
            self.watched_files.insert (file_info.absoluteFilePath(), file_status);
        } else {
            message += "\n" + QString::number(++i) + ". " + file_info.absoluteFilePath() + " is already being watched.";
        }
    }

    emit FileWatcher::logMessage(move(message + "\n"));
}
