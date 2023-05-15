#include "mainwindow.hh"

MainWindow::MainWindow(QWidget * parent):
    QWidget {parent},
    codec {QTextCodec::codecForName("UTF-8")},
    frame {new QFrame {this}},
    inputLabel {new QLabel {this}},
    outputLabel {new QLabel {this}},
    inputEdit {new QLineEdit {this}},
    outputEdit {new QLineEdit {this}},
    nextButton {new QPushButton {this}},
    exitButton {new QPushButton {this}}
{
    setWindowTitle(codec->toUnicode("Возведение в квадрат"));

    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    inputLabel->setText(codec->toUnicode("Введите число:"));
    outputLabel->setText(codec->toUnicode("Результат:"));

    nextButton->setText(codec->toUnicode("Следующее число"));
    exitButton->setText(codec->toUnicode("Выход"));

    QVBoxLayout * edits = new QVBoxLayout {frame};
    edits->addWidget(inputLabel);
    edits->addWidget(inputEdit);
    edits->addWidget(outputLabel);
    edits->addWidget(outputEdit);
    edits->addStretch();

    QVBoxLayout * buttons = new QVBoxLayout {};
    buttons->addWidget(nextButton);
    buttons->addWidget(exitButton);
    buttons->addStretch();

    QHBoxLayout * layout = new QHBoxLayout {this};
    layout->addWidget(frame);
    layout->addLayout(buttons);

    this->reset();

    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::reset);
    connect(inputEdit, &QLineEdit::returnPressed, this, &MainWindow::square);
}

void MainWindow::reset() {
    inputEdit->clear();
    inputEdit->setEnabled(true);
    inputEdit->setFocus();
    outputEdit->setVisible(false);
    outputEdit->setEnabled(false);
    nextButton->setEnabled(false);
    nextButton->setDefault(false);
    outputLabel->setVisible(false);
}

void MainWindow::square() {
    bool parseSuccess;
    float inputNumber = inputEdit->text().toDouble(&parseSuccess);

    if (parseSuccess) {
        outputEdit->setText(QString::number(inputNumber * inputNumber));
        inputEdit->setEnabled(false);
        outputLabel->setVisible(true);
        outputEdit->setVisible(true);
        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();
    }
    else if (!inputEdit->text().isEmpty()) {
        QMessageBox {
            QMessageBox::Information,
            codec->toUnicode("Возведение в квадрат."),
            codec->toUnicode("Введено неверное значение."),
            QMessageBox::Ok
        } .exec();
    }
}
