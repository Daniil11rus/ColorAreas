#ifndef FUNCS_H
#define FUNCS_H

#include <QLineEdit>
#include <QMessageBox>
#include <QRandomGenerator>

static bool checkLineEds(QLineEdit *inWidthLineEd, QLineEdit *inHeightLineEd)
{
    if (inWidthLineEd->text().toInt() <= 0 || inHeightLineEd->text().toInt() <= 0)
    {
        return false;
    }

    return true;
}

static int randomBetween(const int low, const int high)
{
    return QRandomGenerator::global()->bounded(low, high);
}

static bool isAlrEx(const QVector<QColor> &maxColors, QColor color)
{
    for (int i = 0; i < maxColors.size(); ++i)
    {
        if (color == maxColors[i])
        {
            return 1;
        }
    }

    return 0;
}

static void initCoreMatr(const int width, const int height, QVector<QVector<QColor>> &coreMatr)
{
    QVector<QColor> baseColors;
    baseColors << QColor(0, 0, 0) << QColor(255, 255, 255) << QColor (255, 0, 0) << QColor (0, 128, 0)
               << QColor(0, 0, 255) << QColor(0, 255, 0) << QColor(255, 255, 0);
    coreMatr.clear();

    for (int i = 0; i < height; ++i)
    {
        QVector<QColor> line(width);
        coreMatr.push_back(line);

        for (int j = 0; j < width; ++j)
        {
            coreMatr[i][j] = baseColors[randomBetween(0, 6)];
        }
    }
}

static int findSameCol(int currLine, int currColomn, QVector<QVector<QColor>> &coreMatr, QVector<QVector<bool>> &addMatr, int sum)
{
    addMatr[currLine][currColomn] = true;

    if (coreMatr.value(currLine - 1).value(currColomn) == coreMatr[currLine][currColomn] && addMatr.value(currLine - 1).value(currColomn) == false)
    {
        sum += findSameCol(currLine - 1, currColomn, coreMatr, addMatr, 1);
    }
    if (coreMatr.value(currLine).value(currColomn - 1) == coreMatr[currLine][currColomn] && addMatr.value(currLine).value(currColomn - 1) == false)
    {
        sum += findSameCol(currLine, currColomn - 1, coreMatr, addMatr, 1);
    }
    if (coreMatr.value(currLine + 1).value(currColomn) == coreMatr[currLine][currColomn] && addMatr.value(currLine + 1).value(currColomn) == false)
    {
        sum += findSameCol(currLine + 1, currColomn, coreMatr, addMatr, 1);
    }
    if (coreMatr.value(currLine).value(currColomn + 1) == coreMatr[currLine][currColomn] && addMatr.value(currLine).value(currColomn + 1) == false)
    {
        sum += findSameCol(currLine, currColomn + 1, coreMatr, addMatr, 1);
    }

    return sum;
}

static void getAndPrntAnsw(QVector<QVector<QColor>> &coreMatr)
{
    int maxSum = 0;
    QColor maxColor;
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
                maxColor = coreMatr[i][j];
            }
        }
    }

    QMessageBox msg;
    msg.setText(QString::number(maxSum));
    msg.show();
    msg.exec();
}

#endif // FUNCS_H
