#ifndef FILEVIEW_HH
#define FILEVIEW_HH

#include <QWidget>
#include <QFileSystemModel>
#include <QListView>
#include <QPushButton>

class FileView: public QWidget { Q_OBJECT
public:
    explicit FileView(QWidget * parent);

signals:
    void fileSelected(QString const&);

private slots:
    void onFileSelected(QModelIndex const&);
    void onPbOpenFolderClicked();

private:
    QFileSystemModel * model;
    QListView * view;
    QPushButton * pbOpenFolder;
};

#endif // FILEVIEW_HH
