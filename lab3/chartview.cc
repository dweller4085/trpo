#include "chartview.hh"

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPdfWriter>

#include "iocc.hh"

ChartView::ChartView(QWidget * parent, ChartData const& data): QWidget {parent}, data {data} {
    chartView     = new QChartView {};
    cbChartType   = new QComboBox {};
    cbColorScheme = new QComboBox {};
    infoLabel     = new QLabel {};
    pbSaveToPDF   = new QPushButton {"save to pdf"};
    sharedView    = new QStackedWidget {};
    auto layout   = new QVBoxLayout {this};
    auto buttons  = new QHBoxLayout {};
    auto chart    = new QChart {};

    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    cbChartType->setEditable(false);
    cbColorScheme->setEditable(false);
    cbChartType->setMinimumWidth(80);
    cbColorScheme->setMinimumWidth(80);

    for (auto type: gSupportedChartTypes) {
        cbChartType->addItem(asString(type));
    }

    for (auto scheme: gSupportedColorSchemes) {
        cbColorScheme->addItem(asString(scheme));
    }

    updateTemplate(gSupportedChartTypes.first());

    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setFrameStyle(QFrame::StyledPanel);

    cbChartType->setDisabled(true);
    cbColorScheme->setDisabled(true);
    pbSaveToPDF->setDisabled(true);

    displayMessage("Select a file with chart data.", MessageType::Info);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameStyle(QFrame::StyledPanel);
    chartView->setChart(chart);


    auto cbChartTypeLabel = new QLabel {"chart type:"};
    cbChartTypeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    auto cbColorSchemeLabel = new QLabel {"color scheme:"};
    cbColorSchemeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    buttons->addWidget(cbChartTypeLabel);
    buttons->addWidget(cbChartType);
    buttons->addWidget(cbColorSchemeLabel);
    buttons->addWidget(cbColorScheme);
    buttons->addStretch();
    buttons->addWidget(pbSaveToPDF);

    sharedView->addWidget(infoLabel);
    sharedView->addWidget(chartView);

    layout->addWidget(sharedView);
    layout->addLayout(buttons);

    this->setMinimumWidth(420);

    QObject::connect(pbSaveToPDF, &QPushButton::clicked, this, &ChartView::onPbSaveToPDFPressed);
    QObject::connect(cbChartType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartView::onCbChartTypeIndexChanged);
    QObject::connect(cbColorScheme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartView::onCbColorSchemeIndexChanged);
}

void ChartView::drawChart() {
    cbChartType->setDisabled(false);
    cbColorScheme->setDisabled(false);
    pbSaveToPDF->setDisabled(false);

    sharedView->setCurrentIndex((int)SharedView::Chart);

    auto errMsg = QString {};
    auto chartTemplate = gIoCContainer.getService<IChartTemplate>();

    if (!chartTemplate->build(chartView->chart(), data, colorScheme, errMsg)) {
        ChartView::displayMessage(
            QString {} +
            "Could not build a " +
            asString(chartType) +
            " chart with this data.\n" +
            "Hint: " + errMsg +
            "\nPerhaps some other chart type supports this data format?",
            MessageType::Error
        );

        cbColorScheme->setDisabled(true);
        pbSaveToPDF->setDisabled(true);
    }
}

void ChartView::onDataChanged() {
    drawChart();
}

void ChartView::onDataReadFailed(QString const& errMsg) {
    displayMessage(errMsg, MessageType::Error);
    cbChartType->setDisabled(true);
    cbColorScheme->setDisabled(true);
    pbSaveToPDF->setDisabled(true);
}

void ChartView::onChartTypeChanged(ChartType type) {
    chartType = type;
    updateTemplate(type);
    drawChart();
}

void ChartView::onColorSchemeChanged(ColorScheme scheme) {
    colorScheme = scheme;
    applyColorScheme(chartView->chart(), scheme);
}

void ChartView::onPbSaveToPDFPressed() {
    auto filePath = QFileDialog::getSaveFileName(nullptr, "Save chart as a PDF document", {}, "PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    auto pdfWriter = QPdfWriter {filePath};
    auto painter = QPainter {&pdfWriter};
    chartView->render(&painter);
    painter.end();
}

void ChartView::onCbChartTypeIndexChanged(int index) {
    onChartTypeChanged(gSupportedChartTypes[index]);
}

void ChartView::onCbColorSchemeIndexChanged(int index) {
    onColorSchemeChanged(gSupportedColorSchemes[index]);
}

void ChartView::displayMessage(QString const& msg, MessageType type) {
    switch (type) {
        case MessageType::Info: infoLabel->setStyleSheet("QLabel {color: #101010;}"); break;
        case MessageType::Error: infoLabel->setStyleSheet("QLabel {color: #AA1010;}"); break;
    }

    infoLabel->setText(msg);
    sharedView->setCurrentIndex((int)SharedView::Info);
}
