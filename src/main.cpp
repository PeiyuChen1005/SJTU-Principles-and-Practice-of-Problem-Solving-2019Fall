#include "mainwindow.h"
#include <QApplication>
extern int file_flags[211];
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataset.db");
    db.open();
    QSqlQuery query(db);
    int count=0;
    query.exec("select count(*) from record");
    query.next();
    count = query.value(0).toInt();
    qDebug()<<count;
    if(count!=15895268)
    {
        qDebug()<< "Dataset is incomplete,reloading......";
        MyThread *thread=new MyThread();
        thread->start();
    }
    else{
        qDebug()<<"dataset complete!";
        for(int i=0;i<211;++i)
        {
            file_flags[i]=1;
        }
    }
    return app.exec();

}
