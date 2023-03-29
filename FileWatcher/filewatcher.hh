#ifndef FILEWATCHER_HH
#define FILEWATCHER_HH

#include <QObject>
#include <QList>
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

signals:
    void fileChanged (QString const & filepath, ChangeType change, i64 size_diff);
    void logMessage (QString str);

public slots:
    void checkFiles ();

private:
    struct FileStatus__ {
        u64 size;
        bool exists;
    };

    QMap<QString, FileStatus__> watched_files;
};

#endif // FILEWATCHER_HH
