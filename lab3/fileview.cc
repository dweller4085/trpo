#include "fileview.hh"

#include <QVBoxLayout>
#include <QStringList>
#include <QFileDialog>
#include <QDir>

#include "data.hh"

FileView::FileView(QWidget * parent): QWidget {parent} {
    model = new QFileSystemModel {this};
    view = new QListView {this};
    pbOpenFolder = new QPushButton {this};
    auto layout = new QVBoxLayout {this};

    {
        auto filters = QStringList {};
        for (auto format: gSupportedDataFormats) {
            filters << "*." + extension(format);
        } model->setNameFilters(filters);
    }

    model->setFilter(QDir::Files | QDir::NoSymLinks);
    model->setNameFilterDisables(false);
    model->setRootPath(QDir::currentPath());

    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));

    pbOpenFolder->setText(QDir::currentPath());

    layout->addWidget(view);
    layout->addWidget(pbOpenFolder);
    this->setMinimumWidth(220);

    QObject::connect(view, &QListView::activated, this, &FileView::onFileSelected);
    QObject::connect(pbOpenFolder, &QPushButton::clicked, this, &FileView::onPbOpenFolderClicked);
}

void FileView::onPbOpenFolderClicked() {
    auto directory = QFileDialog::getExistingDirectory();
    if (!directory.isEmpty()) {
        model->setRootPath(directory);
        view->setRootIndex(model->index(directory));
        pbOpenFolder->setText(directory);
    }
}

void FileView::onFileSelected(QModelIndex const& index) {
    QModelIndex static previousIndex;

    if (previousIndex != index) {
        emit FileView::fileSelected(model->fileInfo(index));
        previousIndex = index;
    }
}
