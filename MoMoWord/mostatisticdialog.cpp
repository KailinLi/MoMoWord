#include "mostatisticdialog.h"
#include "ui_mostatisticdialog.h"
#include <QDebug>

MoStatisticDialog::MoStatisticDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoStatisticDialog)
{
    ui->setupUi(this);
    backBtn = ui->backBtn;
//    drawSum ();
//    drawDaily ();
}

MoStatisticDialog::~MoStatisticDialog()
{
    delete ui;
}

void MoStatisticDialog::drawDaily()
{
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->dailyCnt->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *oblivion = new QCPBars(ui->dailyCnt->xAxis, ui->dailyCnt->yAxis);
    QCPBars *blurry = new QCPBars(ui->dailyCnt->xAxis, ui->dailyCnt->yAxis);
    QCPBars *remember = new QCPBars(ui->dailyCnt->xAxis, ui->dailyCnt->yAxis);
    oblivion->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    blurry->setAntialiased(false);
    remember->setAntialiased(false);
    oblivion->setStackingGap(1);
    blurry->setStackingGap(1);
    remember->setStackingGap(1);
    // set names and colors:
    remember->setName(tr("认知"));
//    remember->setPen(QPen(QColor(111, 9, 176).lighter(170)));
//    remember->setBrush(QColor(111, 9, 176));
    remember->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    remember->setBrush(QColor(0, 168, 140));
    blurry->setName(tr("模糊"));
    blurry->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    blurry->setBrush(QColor(250, 170, 20));
    oblivion->setName(tr("遗忘"));
    oblivion->setPen(QPen(QColor(255, 52, 106).lighter(130)));
    oblivion->setBrush(QColor(255, 52, 106));
    // stack bars on top of each other:
    blurry->moveAbove(remember);
    oblivion->moveAbove(blurry);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    QVector<double> rememberData, blurryData, oblivionData;
    int maxData = 10;
    QDate currentDate = QDate::currentDate ();

    for (int i = 1; i <= 7; ++i) {
        ticks << i;
        labels << QString::number(currentDate.addDays (i - 7).day ()) + tr("日");
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("select proficiency, count(proficiency) from memory where uid = :uid and \
                      DATE(date) = TIMESTAMPADD(DAY, :date, CURDATE()) group by proficiency");
        query.bindValue(":uid", userID);
        query.bindValue(":date", i - 7);
        query.exec();
        rememberData << 0; blurryData << 0; oblivionData << 0;
        while (query.next ()) {
            maxData = std::max(maxData, query.value (1).toInt ());
            switch (query.value (0).toInt ()) {
            case 1:
                rememberData.pop_back ();
                rememberData << query.value (1).toInt ();
                break;
            case 2:
                blurryData.pop_back ();
                blurryData << query.value (1).toInt ();
                break;
            case 3:
                oblivionData.pop_back ();
                oblivionData << query.value (1).toInt ();
                break;
            }
        }
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->dailyCnt->xAxis->setTicker(textTicker);
    ui->dailyCnt->xAxis->setTickLabelRotation(20);
    QFont qfont = font();
    qfont.setPointSize (1);
    ui->dailyCnt->xAxis->setLabelFont (qfont);
    ui->dailyCnt->xAxis->setSubTicks(false);
    ui->dailyCnt->xAxis->setTickLength(0, 4);
    ui->dailyCnt->xAxis->setRange(0, 8);
    ui->dailyCnt->xAxis->setBasePen(QPen(Qt::white));
    ui->dailyCnt->xAxis->setTickPen(QPen(Qt::white));
    ui->dailyCnt->xAxis->grid()->setVisible(true);
    ui->dailyCnt->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->dailyCnt->xAxis->setTickLabelColor(Qt::white);
    ui->dailyCnt->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->dailyCnt->yAxis->setRange(0, 5 *((maxData / 5) + 1));
    ui->dailyCnt->yAxis->setPadding(5); // a bit more space to the left border
//    ui->dailyCnt->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
//    ui->dailyCnt->yAxis->ticker()->setTickCount(1);
    ui->dailyCnt->yAxis->setBasePen(QPen(Qt::white));
    ui->dailyCnt->yAxis->setTickPen(QPen(Qt::white));
    ui->dailyCnt->yAxis->setSubTickPen(QPen(Qt::white));
    ui->dailyCnt->yAxis->grid()->setSubGridVisible(true);
    ui->dailyCnt->yAxis->setTickLabelColor(Qt::white);
    ui->dailyCnt->yAxis->setLabelColor(Qt::white);
    ui->dailyCnt->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->dailyCnt->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
//    QVector<double> rememberData, blurryData, oblivionData;
//    rememberData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
//    blurryData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
//    oblivionData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    remember->setData(ticks, rememberData);
    blurry->setData(ticks, blurryData);
    oblivion->setData(ticks, oblivionData);

    // setup legend:
    ui->dailyCnt->legend->setVisible(true);
    ui->dailyCnt->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->dailyCnt->legend->setBrush(QColor(255, 255, 255, 100));
    ui->dailyCnt->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->dailyCnt->legend->setFont(legendFont);
    ui->dailyCnt->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MoStatisticDialog::drawSum()
{

    QVector<QVector<double>> cnt (4, QVector<double>(7, 0));
    for (int i = 0; i < 7; ++i) {
        QSqlQuery query(QSqlDatabase::database("momoword"));
        query.prepare("select avg(proficiency) from memory where uid = :uid and \
                      DATE(date) <= TIMESTAMPADD(DAY, :bdate, CURDATE()) and \
                      DATE(date) > TIMESTAMPADD(DAY, :edate, CURDATE()) group by wid");
        query.bindValue(":uid", userID);
        query.bindValue(":bdate", i - 6);
        query.bindValue(":edate", i - 12);
        query.exec ();
        while (query.next ()) {
            if (query.value (0).toInt () <= 1.1)
                ++cnt[0][i];
            else if (query.value (0).toInt () <= 1.3)
                ++cnt[1][i];
            else if (query.value (0).toInt () <= 2.0)
                ++cnt[2][i];
            else ++cnt[3][i];
        }
    }
    double maxCnt = 0;
    QVector<double> x(7);
    QVector<double> y1(7);
    QVector<double> y2(7);
    QVector<double> y3(7);
    QVector<double> y4(7);
    for (int i = 0; i < 7; ++i) {
        x[i] = i + 1;
        y1[i] = cnt[0][i];
        y2[i] = cnt[1][i];
        y3[i] = cnt[2][i];
        y4[i] = cnt[3][i];
        maxCnt = std::max({cnt[0][i], cnt[1][i], cnt[2][i], cnt[3][i], maxCnt});
    }

    QCPGraph *graph1 = ui->sumCnt->addGraph();
    graph1->setData(x, y1);
    graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDiamond,
                                            QPen(QColor(0, 138, 92), 0.5), QBrush(Qt::white), 7));
    graph1->setPen(QPen(QColor(0, 138, 92), 2));

    QCPGraph *graph2 = ui->sumCnt->addGraph();
    graph2->setData(x, y2);
    graph2->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                                            QPen(QColor(0, 168, 140), 0.5), QBrush(Qt::white), 7));
    graph2->setPen(QPen(QColor(0, 168, 140), 2));
    graph2->setChannelFillGraph(graph1);

    QCPGraph *graph3 = ui->sumCnt->addGraph();
    graph3->setData(x, y3);
    graph3->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare,
                                            QPen(QColor(250, 170, 20), 0.5), QBrush(Qt::white), 7));
    graph3->setPen(QPen(QColor(250, 170, 20), 2));
    graph3->setChannelFillGraph(graph2);

    QCPGraph *graph4 = ui->sumCnt->addGraph();
    graph4->setData(x, y4);
    graph4->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle,
                                            QPen(QColor(255, 52, 106), 0.5), QBrush(Qt::white), 7));
    graph4->setPen(QPen(QColor(255, 52, 106), 2));
    graph4->setChannelFillGraph(graph3);

    // move bars above graphs and grid below bars:
    ui->sumCnt->addLayer("abovemain", ui->sumCnt->layer("main"), QCustomPlot::limAbove);
    ui->sumCnt->addLayer("belowmain", ui->sumCnt->layer("main"), QCustomPlot::limBelow);
    graph1->setLayer("abovemain");
    ui->sumCnt->xAxis->grid()->setLayer("belowmain");
    ui->sumCnt->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    ui->sumCnt->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->sumCnt->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->sumCnt->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->sumCnt->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->sumCnt->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->sumCnt->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->sumCnt->xAxis->setTickLabelColor(Qt::white);
    ui->sumCnt->yAxis->setTickLabelColor(Qt::white);
    ui->sumCnt->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->sumCnt->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->sumCnt->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->sumCnt->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->sumCnt->xAxis->grid()->setSubGridVisible(true);
    ui->sumCnt->yAxis->grid()->setSubGridVisible(true);
    ui->sumCnt->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->sumCnt->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->sumCnt->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->sumCnt->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->sumCnt->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->sumCnt->axisRect()->setBackground(axisRectGradient);

    ui->sumCnt->rescaleAxes();
    ui->sumCnt->yAxis->setRange(0, 5 * (maxCnt / 5 + 1));

}
