#include "mainwindow.h"
#include "mythread.h"
QStringList files;
int file_flags[211]={0};
MyThread::MyThread()
{
}

void MyThread::get_file_names()
{
    QDir dir("D:/SJTU/sjtu/PPPS/Final Project/dataset_CS241/dataset");
    QStringList nameFilters;
    nameFilters << "*.csv";
    QStringList names =dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    qDebug()<<names.count()<<endl;
    const QString prev_dir="D:/SJTU/sjtu/PPPS/Final Project/dataset_CS241/dataset/";
    for(int i=0;i<names.count();++i)
    {
        QString tmp=prev_dir+names.at(i);
        files.append(tmp);
    }
}

void MyThread::run()
{
    this->get_file_names();
    //qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataset.db");
    //db.setUserName("root" );
    //db.setPassword("123456");

    if(!db.open()){
        qDebug()<<"error info :"<<db.lastError();
    }
    else{
        QSqlQuery query;
        query.exec("drop table if exists record");
        QString creatTableStr = "create table if not exists record \
                (                                      \
                    time      char  NULL ,         \
                    lineID    char      NULL ,         \
                    stationID int       NULL ,         \
                    status    int   NULL ,         \
                    payType   int   NULL          \
                    );";
        query.prepare(creatTableStr);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"creat table success!";
        }
    }
    for(int i=0;i<files.size();++i)
    {
        QTime   tmpTime;
        tmpTime.start();
        QFile file(files.at(i));
        QVector<QStringList> data;
        if(!file.exists()){
            qDebug() << "file not exists! " << files.at(i);
        }
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Cannot open file for reading: "
                     << file.errorString()<<endl;
            qDebug() << "can't open"<<endl;
        }
        //qDebug() << files.at(i);


        else{
            QTextStream stream(&file);
            for(;;){
                QString line = stream.readLine();
                if(line.isEmpty()){
                    break;
                }
                QStringList row;
                for(const QString& cell: line.split(",")){
                    row.append(cell);
                }
                data.push_back(row);
            }
            file.close();
        }
        if(db.open())
        {
            QSqlQuery query;
            db.transaction();
            for(int j=1;j<data.size();++j)
            {
                {
                    query.prepare("INSERT INTO record (time,lineID,stationID,status,payType)"
                                  "VALUES (:time,:lineID,:stationID,:status,:payType)");
                    QStringList tmp=data.at(j);


                    query.bindValue(":time", tmp[0]);


                    query.bindValue(":lineID", tmp[1]);
                    QString _tmp=tmp[2];
                    query.bindValue(":stationID", tmp[2]);

                    _tmp=tmp[4];
                    query.bindValue(":status", _tmp.toInt());

                    _tmp=tmp[6];
                    query.bindValue(":payType", _tmp.toInt());

                    query.exec();
                }
            }
            db.commit();
        }
        db.close();
        qDebug()<<"File"<<i<<":"<<tmpTime.elapsed()<<"ms"<<endl;
        //db.removeDatabase("QSQLITE");
        file_flags[i]=1;
    }

    db.open();
    QSqlQuery query(db);
    query.exec("CREATE INDEX t_s_s_index ON record(time,stationID,status);");
    qDebug()<<"Index created!";
    db.close();
    file_flags[210]=1;
}


