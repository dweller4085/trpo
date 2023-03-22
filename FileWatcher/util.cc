#include <QtDebug>
#include "util.hh"

fn read_args (char const * const * argv) -> QList<QString> {
    let vec = QList<QString> {};
    while (*(++argv) != nullptr) {
        vec.push_back(QString {*argv});
    }

    return vec;
}

fn static operator << (QDebug debug, FileWatcher::ChangeType change) -> QDebug {
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

fn report_file_change (QString const & filepath, FileWatcher::ChangeType change, i64 size_diff) -> void {
    qInfo().nospace() <<
        "Registered a change!" <<
        "\nFile: " << filepath <<
        "\nChange: " << change <<
        "\nSize change: " << (size_diff > 0 ? "+" : "") << size_diff <<
        "\n"
    ;
}
