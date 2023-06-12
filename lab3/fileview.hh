#pragma once

#include <QFileSystemModel>
#include <QPushButton>
#include <QListView>
#include <QFileInfo>
#include <QWidget>

class FileView: public QWidget { Q_OBJECT
public:
    explicit FileView(QWidget * parent);

signals:
    void fileSelected(QFileInfo const&);

private slots:
    void onFileSelected(QModelIndex const&);
    void onPbOpenFolderClicked();

private:
    QFileSystemModel * model;
    QListView * view;
    QPushButton * pbOpenFolder;
};
