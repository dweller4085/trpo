#include <QtDebug>
#include "util.hh"

QList<QString> read_args (char const * const * argv) {
    let vec = QList<QString> {};
    while (*(++argv) != nullptr) {
        vec.push_back(QString {*argv});
    }

    return vec;
}

static QDebug operator << (QDebug debug, FileWatcher::ChangeType change) {
    QDebugStateSaver saver {debug};
    
    static char const * const names [] {
        "Size Changed",
        "Created",
        "Deleted",
        "Unchanged"
    };
    
    debug.nospace() << names [usize (change)];

    return debug;
}

void report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff) {
    qInfo().nospace() <<
        "Registered a change!" <<
        "\nFile: " << filepath <<
        "\nChange: " << change <<
        "\nSize change: " << (size_diff > 0 ? "+" : "") << size_diff <<
        "\n"
    ;
}
