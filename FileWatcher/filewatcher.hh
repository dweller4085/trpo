#ifndef FILEWATCHER_HH
#define FILEWATCHER_HH

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include "common.hh"

class FileWatcher : public QObject { Q_OBJECT
public:
    enum class ChangeType : usize {
        SizeChanged,
        Created,
        Deleted,
        Unchanged
    };

    FileWatcher (FileWatcher const &) = delete;
    FileWatcher (FileWatcher &&) = delete;

    static FileWatcher & instance ();

    QList<QString> getWatchedFiles () const;
    void setWatchedFiles (QList<QString> files);
    void addFile (QString filename);

private:
    FileWatcher ();
    explicit FileWatcher (QObject * parent);
    ~FileWatcher () = default;

    struct FileStatus {
        u64 size;
        bool exists;
    };

    QMap<QString, FileStatus> watched_files;

signals:
    void fileChanged (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff);
    void logMessage (QString str);

public slots:
    void checkFiles ();
};

#endif // FILEWATCHER_HH
