#include <QtDebug>
#include "util.hh"

fn read_args (char const * const * argv) -> QVector<QString> {
    let vec = QVector<QString> {};
    while (*(++argv) != nullptr) {
        vec.push_back (QString {*argv});
    }

    ret vec;
}

static QDebug operator << (QDebug debug, FileWatcher::ChangeType change) {
    QDebugStateSaver saver(debug);
    
    static char const * const names [] {
        "Size Changed",
        "Created",
        "Deleted"
    };
    
    debug.nospace() << names [usize (change)];

    return debug;
}

fn report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_change) -> void {
    qInfo () << "File changed: " << filepath << "\nChange:" << change << "\nSize change: " << size_change << "\n";
}
