#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QPushButton>
#include <QtCharts>
#include <QtWidgets>
#include <QVector>
#include <QPieSeries>
#include <QPieSlice>
#include <QTime>
#include <QVector>
#include <QTextStream>
#include <QTextBrowser>
#include "mythread.h"
#include <QMutex>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QChartView>
#include <QLineSeries>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void import_map();
    void possible_routes(int x,int y,int cnt);
    bool file_flag=false;
    void print_routes(QVector<QVector<QString>> _vec);
public slots:
    void on_routes_clicked();
    void on_load_data_clicked();
private:
    Ui::MainWindow *ui;
private slots:
    void on_trend_clicked();
};

#endif // MAINWINDOW_H
