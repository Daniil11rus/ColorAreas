#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "funcs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupWidgets();
    void drawCoreMatr();
    void getAndPrntAnsw();

public slots:
    void calcButtClicked();

protected:
    virtual void paintEvent(QPaintEvent *qPaintEv);

private:
    Ui::MainWindow *ui;
    QLabel *inWidthLabel;
    QLabel *inHeightLabel;
    QLabel *outLabel;
    QLineEdit *inWidthLineEd;
    QLineEdit *inHeightLineEd;
    QPushButton *calcButt;

    QVector<QVector<QColor>> coreMatr;

    void setupInWidthLabel();
    void setupInHeightLabel();
    void setupOutLabel();
    void setupInWidthLineEd();
    void setupInHeightLineEd();
    void setupCalcButt();
};
#endif // MAINWINDOW_H
