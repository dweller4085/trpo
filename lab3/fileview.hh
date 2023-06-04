#ifndef FILEVIEW_HH
#define FILEVIEW_HH

#include <QWidget>
#include <QFileSystemModel>
#include <QListView>
#include <QPushButton>

class FileView: public QWidget { Q_OBJECT
public:
    explicit FileView(QWidget * parent);

private:
    QFileSystemModel * model;
    QListView * view;
    QPushButton * openFolder;
};

#endif // FILEVIEW_HH
