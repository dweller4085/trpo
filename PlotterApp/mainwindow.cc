#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(): QMainWindow(nullptr) {
    ui = new Ui::MainWindow {};
    ui->setupUi(this);
    fsModel = new QFileSystemModel {this};
    fsModel->setRootPath("C:\\");
    ui->treeView->setModel(fsModel);
}

MainWindow::~MainWindow() {
    delete ui;
}
