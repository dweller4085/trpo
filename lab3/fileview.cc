#include "fileview.hh"
#include <QVBoxLayout>
#include <QDir>

FileView::FileView(QWidget * parent): QWidget {parent} {
    model = new QFileSystemModel {this};
    model->setRootPath(QDir::currentPath());
    view = new QListView {this};
    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));
    openFolder = new QPushButton {this};
    openFolder->setText("C:\\");
    auto layout = new QVBoxLayout {this};
    layout->addWidget(view);
    layout->addWidget(openFolder);
    this->setMinimumWidth(200);

    //this doesnt work
    //this->sizePolicy().setHorizontalStretch(1);
}
