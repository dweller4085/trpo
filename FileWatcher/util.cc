#include "util.hh"

fn read_args (char const * const * argv) -> QVector<QString> {
    let vec = QVector<QString> {};
    while (*(++argv) != nullptr) {
        vec.push_back (QString {*argv});
    }

    ret vec;
}
