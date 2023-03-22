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

    FileWatcher ();
    explicit FileWatcher (QObject * parent);
    explicit FileWatcher (QVector<QString> const & files_to_watch);
    ~FileWatcher () = default;

    QList<QString> getWatchedFiles () const;
    void setWatchedFiles (QList<QString> files);
    void addFile (QString filename);

signals:
    void fileChanged (QString const & filepath, ChangeType change, i64 size_diff);
    void logMessage (QString str);

public slots:
    void checkFiles ();

private:
    struct File {
        QString path;
        u64 size;
        bool exists;
    };

    QList<File> watched_files;
};

#endif // FILEWATCHER_HH
