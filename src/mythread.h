#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "mainwindow.h"
class MyThread : public QThread
{
public:
    MyThread();
    QString name;
    void run();
    void get_file_names();
    int file_flag[210];
private:
    //volatile bool isStop;       //isStop是易失性变量，需要用volatile进行申明
};

#endif // MYTHREAD_H
