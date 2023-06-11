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

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFrameStyle(QFrame::StyledPanel);
    //chartView->setChart(chart);
    chartView->chart()->setContentsMargins(0, 0, 0, 0);
    chartView->chart()->setBackgroundRoundness(0);

    buttons->addWidget(cbChartType);
    buttons->addWidget(cbColorScheme);
    buttons->addStretch();
    buttons->addWidget(pbSaveToPDF);

    sharedView->addWidget(chartView);
    sharedView->addWidget(infoLabel);

    layout->addWidget(sharedView);
    layout->addLayout(buttons);

    this->setMinimumWidth(360);

    QObject::connect(pbSaveToPDF, &QPushButton::clicked, this, &ChartView::onPbSaveToPDFPressed);
}

void ChartView::drawChart() {
    auto chart = gIoCContainer.getService<IChartTemplate>()->build(data, colorScheme);
    chartView->setChart(chart);
    sharedView->setCurrentIndex(Chart);
}

void ChartView::onDataChanged() {
    drawChart();
}

void ChartView::onDataInvalidated(QString const& errorMsg) {
    infoLabel->setText(errorMsg);
    infoLabel->setStyleSheet("{color: #AA1010}");
    sharedView->setCurrentIndex(Info);
}

void ChartView::onChartTypeChanged(ChartType type) {
    updateTemplate(type);
    drawChart();
}

void ChartView::onColorSchemeChanged(ColorScheme scheme) {
    setColorScheme(chartView->chart(), scheme);
}

void ChartView::onPbSaveToPDFPressed() {
    auto filePath = QFileDialog::getSaveFileName(nullptr, "Save chart as PDF", {}, "PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    auto pdfWriter = QPdfWriter {filePath};
    auto painter = QPainter {&pdfWriter};
    chartView->render(&painter);
    painter.end();
}
