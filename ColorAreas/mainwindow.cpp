#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupWidgets();

    QObject::connect(calcButt, SIGNAL(clicked()), this, SLOT(calcButtClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcButtClicked()
{
    if (checkLineEds(inWidthLineEd, inHeightLineEd))
    {
        int width = inWidthLineEd->text().toInt();
        int height = inHeightLineEd->text().toInt();

        initCoreMatr(width, height, coreMatr);
        drawCoreMatr();
        getAndPrntAnsw();
    }
}

void MainWindow::getAndPrntAnsw()
{
    int maxSum = 0;
    QVector<QColor> maxColors;
    QVector<QVector<bool>> addMatr;

    for (int k = 0; k < coreMatr.size(); ++k)
    {
        QVector<bool> line(coreMatr[k].size());
        addMatr.push_back(line);

        for (int l = 0; l < addMatr[k].size(); ++l)
        {
            addMatr[k][l] = false;
        }
    }

    for (int i = 0; i < coreMatr.size(); ++i)
    {
        for (int j = 0; j < coreMatr[i].size(); ++j)
        {
            if (addMatr[i][j] == true)
            {
                continue;
            }
            int sum = findSameCol(i, j, coreMatr, addMatr, 1);

            if (sum > maxSum)
            {
                maxSum = sum;
                maxColors.clear();
                maxColors.push_back(coreMatr[i][j]);
            }
            else if (sum == maxSum && !isAlrEx(maxColors, coreMatr[i][j]))
            {
                maxColors.push_back(coreMatr[i][j]);
            }
        }
    }

    QVector<QString> maxColorsStr;
    for (int i = 0; i < maxColors.size(); ++i)
    {
        if (maxColors[i] == QColor(255, 255, 255))
        {
            maxColorsStr.push_back("белый");
        }
        else if (maxColors[i] == QColor(0, 0, 0))
        {
            maxColorsStr.push_back("черный");
        }
        else if (maxColors[i] == QColor(255, 0, 0))
        {
            maxColorsStr.push_back("красный");
        }
        else if (maxColors[i] == QColor(0, 128, 0))
        {
            maxColorsStr.push_back("зеленый");
        }
        else if (maxColors[i] == QColor (0, 0, 255))
        {
            maxColorsStr.push_back("синий");
        }
        else if (maxColors[i] == QColor (0, 255, 0))
        {
            maxColorsStr.push_back("лаймовый");
        }
        else if (maxColors[i] == QColor (255, 255, 0))
        {
            maxColorsStr.push_back("желтый");
        }
    }

    QMessageBox msg;
    msg.setWindowTitle("Ответ");
    msg.setText("Ответ: " + QString::number(maxSum) + ".\nСоответствующие цвета: " + maxColorsStr[0]);
    for (int i = 1; i < maxColorsStr.length(); ++i)
    {
        msg.setText(msg.text() + ", " + maxColorsStr[i]);
    }
    msg.setText(msg.text() + ".");
    msg.show();
    msg.exec();
}

void MainWindow::paintEvent(QPaintEvent *qPaintEv)
{
    Q_UNUSED(qPaintEv);

    QPainter painter(this);

    for (int i = 0; i < coreMatr.size(); ++i)
    {
        for (int j = 0; j < coreMatr[i].size(); ++j)
        {
            painter.fillRect(10 + j * 50, 50 + i * 50, 50, 50, coreMatr[i][j]);
            painter.drawRect(10 + j * 50, 50 + i * 50, 50, 50);
        }
    }
}

void MainWindow::drawCoreMatr()
{
    this->repaint();
}

void MainWindow::setupInWidthLabel()
{
    inWidthLabel = new QLabel("Ширина: ", this);
    inWidthLabel->setGeometry(QRect(QPoint(10, 10), QSize(50, 30)));
    inWidthLabel->show();
}

void MainWindow::setupInWidthLineEd()
{
    inWidthLineEd = new QLineEdit(this);
    inWidthLineEd->setGeometry(QRect(QPoint(70, 10), QSize(50, 30)));
    inWidthLineEd->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), inWidthLineEd));
    inWidthLineEd->show();
}

void MainWindow::setupInHeightLabel()
{
    inHeightLabel = new QLabel("Высота: ", this);
    inHeightLabel->setGeometry(QRect(QPoint(150, 10), QSize(50, 30)));
    inHeightLabel->show();
}

void MainWindow::setupInHeightLineEd()
{
    inHeightLineEd = new QLineEdit(this);
    inHeightLineEd->setGeometry(QRect(QPoint(210, 10), QSize(50, 30)));
    inHeightLineEd->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), inHeightLineEd));
    inHeightLineEd->show();
}

void MainWindow::setupCalcButt()
{
    calcButt = new QPushButton("Посчитать", this);
    calcButt->setGeometry(QRect(QPoint(320, 10), QSize(70, 30)));
    calcButt->show();
}

void MainWindow::setupWidgets()
{
    setupInWidthLabel();
    setupInWidthLineEd();

    setupInHeightLabel();
    setupInHeightLineEd();

    setupCalcButt();
}
