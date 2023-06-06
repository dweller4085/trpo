#include "fileview.hh"
#include <QVBoxLayout>
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include "common.hh"

FileView::FileView(QWidget * parent): QWidget {parent} {
    model = new QFileSystemModel {this};
    view = new QListView {this};
    pbOpenFolder = new QPushButton {this};
    auto layout = new QVBoxLayout {this};

    {
        auto filters = QStringList {};
        for (auto format: gSupportedDataFormats) {
            filters << format.asExtension();
        }
        model->setNameFilters(filters);
    }

    model->setFilter(QDir::Files);
    model->setNameFilterDisables(false);
    model->setRootPath(QDir::currentPath());

    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));

    pbOpenFolder->setText(QDir::currentPath());

    layout->addWidget(view);
    layout->addWidget(pbOpenFolder);
    this->setMinimumWidth(360);

    QObject::connect(view, &QListView::activated, this, &FileView::onFileSelected);
    QObject::connect(pbOpenFolder, &QPushButton::clicked, this, &FileView::onPbOpenFolderClicked);
}

void FileView::onPbOpenFolderClicked() {
    auto directory = QFileDialog::getExistingDirectory();
    model->setRootPath(directory);
    view->setRootIndex(model->index(directory));
    pbOpenFolder->setText(directory);
}

void FileView::onFileSelected(QModelIndex const& index) {
    QModelIndex static previousIndex;

    if (previousIndex != index) {
        emit FileView::fileSelected(model->filePath(index));
        previousIndex = index;
    }
}
