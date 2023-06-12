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

    buttons->addWidget(new QLabel {"chart type:"});
    buttons->addWidget(cbChartType);
    buttons->addWidget(new QLabel {"color scheme:"});
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

    auto errMsg = QString {};
    auto chart = gIoCContainer.getService<IChartTemplate>()->build(data, colorScheme, errMsg);

    if (!chart) {
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

        return;
    }

    auto oldChart = chartView->chart();
    chartView->setChart(chart);
    delete oldChart;

    sharedView->setCurrentIndex((int)SharedView::Chart);

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
