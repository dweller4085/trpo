#include "fileview.hh"
#include <QVBoxLayout>
#include <QDir>

FileView::FileView(QWidget * parent): QWidget {parent} {
    model = new QFileSystemModel {this};
    view = new QListView {this};
    pbOpenFolder = new QPushButton {this};
    auto layout = new QVBoxLayout {this};

    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    model->setRootPath(QDir::currentPath());

    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));

    pbOpenFolder->setText(QDir::currentPath());

    layout->addWidget(view);
    layout->addWidget(pbOpenFolder);
    this->setMinimumWidth(360);

    QObject::connect(view, &QListView::clicked, this, &FileView::onFileSelected);
    QObject::connect(pbOpenFolder, &QPushButton::clicked, this, &FileView::onPbOpenFolderClicked);

}
