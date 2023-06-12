#include "chartview.hh"

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPdfWriter>

#include "iocc.hh"

ChartView::ChartView(QWidget * parent, ChartData const& data): QWidget {parent}, data {data} {
    chartView = new QChartView {};
    cbChartType = new QComboBox {};
    cbColorScheme = new QComboBox {};
    infoLabel = new QLabel {};
    pbSaveToPDF = new QPushButton {"save to pdf"};
    sharedView = new QStackedWidget {};

    auto layout = new QVBoxLayout {this};
    auto buttons = new QHBoxLayout {};

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

    cbChartType->setCurrentIndex(2);
    updateTemplate(ChartType::Line);

    cbChartType->setDisabled(true);
    cbColorScheme->setDisabled(true);
    pbSaveToPDF->setDisabled(true);

    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setText("Select a file with chart data.");

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameStyle(QFrame::StyledPanel);

    buttons->addWidget(cbChartType);
    buttons->addWidget(cbColorScheme);
    buttons->addStretch();
    buttons->addWidget(pbSaveToPDF);

    sharedView->addWidget(infoLabel);
    sharedView->addWidget(chartView);

    layout->addWidget(sharedView);
    layout->addLayout(buttons);

    this->setMinimumWidth(360);

    QObject::connect(pbSaveToPDF, &QPushButton::clicked, this, &ChartView::onPbSaveToPDFPressed);
    QObject::connect(cbChartType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartView::onCbChartTypeIndexChanged);
    QObject::connect(cbColorScheme, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartView::onCbColorSchemeIndexChanged);
}

void ChartView::drawChart() {
    auto chart = gIoCContainer.getService<IChartTemplate>()->build(data, colorScheme);
    chartView->setChart(chart);
    sharedView->setCurrentIndex((int)SharedView::Chart);
    cbChartType->setDisabled(false);
    cbColorScheme->setDisabled(false);
    pbSaveToPDF->setDisabled(false);
}

void ChartView::onDataChanged() {
    drawChart();
}

void ChartView::onDataInvalidated(QString const& errorMsg) {
    infoLabel->setText(errorMsg);
    infoLabel->setStyleSheet("QLabel {color: #AA1010;}");
    sharedView->setCurrentIndex((int)SharedView::Info);
    cbChartType->setDisabled(true);
    cbColorScheme->setDisabled(true);
    pbSaveToPDF->setDisabled(true);
}

void ChartView::onChartTypeChanged(ChartType type) {
    updateTemplate(type);
    drawChart();
}

void ChartView::onColorSchemeChanged(ColorScheme scheme) {
    applyColorScheme(chartView->chart(), scheme);
}

void ChartView::onPbSaveToPDFPressed() {
    auto filePath = QFileDialog::getSaveFileName(nullptr, "Save chart as PDF", {}, "PDF (*.pdf)");
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
