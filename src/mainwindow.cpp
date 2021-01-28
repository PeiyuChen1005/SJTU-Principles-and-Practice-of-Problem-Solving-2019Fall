#include "mainwindow.h"
#include "ui_mainwindow.h"

int count=0;
QVector<QVector<QString>> metro_map(81, QVector<QString>(81));
QVector<QVector<QString>> routes;
QVector<QString>route;
QVector<QString>shortest_route;
QVector<int> score;
QVector<int> loss;
int congestion_degree[81]={139296,88578,243299,179594,461105,279908,135871,435084,324189,661224,376001,363729,349504,289158,276662,1220184,302524,96323,227420,138612,339404,89499,308374,141455,256796,237685,136480,124585,59294,136859,10479,55756,109320,306643,100192,59836,82046,143671,147416,168705,86439,136015,173726,141314,143200,159894,262003,229947,154908 ,205755,170004,165801,207225,249493,0,218979,257684,216234,191423,195679 ,137824,156259,151691,159064,73405,116270,83548,91569,84772,140092,133120,88041,55007,150987,43841,179889,212531,197171,229642,85172,62573};
int _visited[81];
int _path[81];
int routes_number=0;
extern int file_flags[211];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle(tr("HangZhou Metro"));
    setFixedSize(this->width(),this->height());
    QMessageBox *message =new QMessageBox();
    message->setText("Loading takes a long time for the first timem,please wait.After that data loading will be quick.");
    message->setWindowTitle("Tips");
    message->show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataset.db");
    db.open();
    QSqlQuery query(db);
    query.exec("select count(*) from record");
    query.next();
    count = query.value(0).toInt();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::possible_routes(int x,int y,int cnt)
{
    int i;
    _visited[x] = 1;
    _path[cnt] = x;
    if (x == y)
    {
        //QString n=QString::number(routes_number);
        //ui->routes_shown->append("Routes");
        //ui->routes_shown->insertPlainText(n);
        //ui->routes_shown->insertPlainText(":");
        for (i = 0; i <= cnt; i++)
        {
            //qDebug() << _path[i]+1;
            QString r=QString::number(_path[i]);
            route.push_back(r);
            //ui->routes_shown->insertPlainText(r);
            //ui->routes_shown->insertPlainText("->");
        }
        routes.push_back(route);
        route.clear();
    }
    for (i = 0; i < 81; i++)
    {
        if (metro_map[x][i]=='1' && !_visited[i])
        {
            //vis[i] = 1;
            possible_routes(i, y, cnt + 1);
        }
    }
    _visited[x] = 0;
}

void MainWindow::print_routes(QVector<QVector<QString> > _vec)
{
    QVector<QVector<QString>>::iterator it1;
    QVector<QString>::iterator it2;
    QVector<QString>tmp;
    int size=81;
    double _score=INT_MAX*1.0;
    shortest_route.clear();
    for(it1=_vec.begin();it1!=_vec.end();it1++)
    {
        tmp=*it1;
        if(tmp.size()<size)
        {
            size=tmp.size();
            shortest_route=tmp;
        }
    }
    if(!ui->all_routes->isChecked()&&!ui->shortest_routes->isChecked()&&!ui->re_route->isChecked()&&!ui->le_route->isChecked())
    {
        QMessageBox *message=new QMessageBox();
        message->setText("Please select your choice.");
        message->setWindowTitle("Warning");
        message->show();
    }
    else
    {
        if(ui->shortest_routes->isChecked()&&!ui->all_routes->isChecked()&&!ui->re_route->isChecked()&&!ui->le_route->isChecked())
        {
            ui->show_routes->clear();
            ui->show_routes->insertPlainText("The Shortest Route: ");
            for(int i=0;i<shortest_route.size()-1;++i)
            {
                ui->show_routes->insertPlainText(shortest_route[i]);
                ui->show_routes->insertPlainText("->");
            }
            {
                ui->show_routes->insertPlainText(shortest_route[shortest_route.size()-1]);
            }
        }
        else if(ui->all_routes->isChecked()&&!ui->shortest_routes->isChecked()&&!ui->re_route->isChecked()&&!ui->le_route->isChecked())
        {
            ui->show_routes->clear();
            int i=1;
            QVector<QVector<QString>>::iterator it1;
            QVector<QString>::iterator it2;
            QVector<QString>tmp;
            for(it1=_vec.begin();it1!=_vec.end();it1++)
            {
                tmp=*it1;
                ui->show_routes->insertPlainText("Routes"+QString::number(i)+": ");
                for(it2=tmp.begin();it2!=tmp.end()-1;it2++)
                {
                    ui->show_routes->insertPlainText(*it2);
                    ui->show_routes->insertPlainText("->");
                }
                it2=tmp.end()-1;
                ui->show_routes->insertPlainText(*it2);
                i++;
                ui->show_routes->appendPlainText("\n");
            }
        }
        else if(ui->le_route->isChecked()&&!ui->all_routes->isChecked()&&!ui->shortest_routes->isChecked()&&!ui->re_route->isChecked())
        {
            double score=0;
            QVector<QString>le_route;
            ui->show_routes->clear();
            ui->show_routes->insertPlainText("The Least Crowded Route: ");
            QVector<QVector<QString>>::iterator it1;
            QVector<QString>::iterator it2;
            QVector<QString>tmp;
            for(it1=_vec.begin();it1!=_vec.end();it1++)
            {
                score=0;
                tmp=*it1;
                for(it2=tmp.begin();it2!=tmp.end();it2++)
                {
                    QString tmp_str=*it2;
                    score+= congestion_degree[tmp_str.toInt()];
                }
                if(score<_score)
                {
                    _score=score;
                    le_route=tmp;
                }
            }
            QVector<QString>::iterator it3;
            for(it3=le_route.begin();it3!=le_route.end()-1;it3++)
            {
                ui->show_routes->insertPlainText(*it3);
                ui->show_routes->insertPlainText("->");
            }
            it3=le_route.end()-1;
            ui->show_routes->insertPlainText(*it3);
            ui->show_routes->appendPlainText("\n");
            //qDebug()<<_score;
        }
        else if(ui->re_route->isChecked()&&!ui->all_routes->isChecked()&&!ui->shortest_routes->isChecked()&&!ui->le_route->isChecked())
        {
            _score=INT_MAX*1.0;
            double score=0;
            QVector<QString>re_route;
            ui->show_routes->clear();
            ui->show_routes->insertPlainText("The Recommended Route: ");
            QVector<QVector<QString>>::iterator it1;
            QVector<QString>::iterator it2;
            QVector<QString>tmp;
            for(it1=_vec.begin();it1!=_vec.end();it1++)
            {
                score=0;
                tmp=*it1;
                for(it2=tmp.begin();it2!=tmp.end()-1;it2++)
                {
                    QVector<QString>::iterator it2_next=it2+1;
                    QString tmp_str=*it2;
                    QString tmp_str_n=*it2_next;
                    score+= congestion_degree[tmp_str.toInt()]/100000.00;
                    score+=abs(tmp_str.toInt()-tmp_str_n.toInt());
                }

                {
                    it2=tmp.end()-1;
                    QString tmp_str=*it2;
                    score+=congestion_degree[tmp_str.toInt()]/100000.00;
                    score+=tmp.size();
                }
                if(score<_score)
                {
                    _score=score;
                    re_route=tmp;
                }
            }
            QVector<QString>::iterator it3;
            for(it3=re_route.begin();it3!=re_route.end()-1;it3++)
            {
                ui->show_routes->insertPlainText(*it3);
                ui->show_routes->insertPlainText("->");
            }
            it3=re_route.end()-1;
            ui->show_routes->insertPlainText(*it3);
            ui->show_routes->appendPlainText("\n");

        }
        else
        {
            QMessageBox *message=new QMessageBox();
            message->setText("Select only one choice.");
            message->setWindowTitle("Warning");
            message->show();
        }
    }
}



void MainWindow::import_map()
{
    QFile inFile("D:\\Metro_roadMap.csv");
    QStringList lines;/*行数据*/
    if (inFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream_text(&inFile);
        while (!stream_text.atEnd())
        {
            lines.push_back(stream_text.readLine());
        }
        for (int i = 1; i < lines.size(); i++)
        {
            QString line = lines.at(i);
            QStringList split = line.split(",");/*列数据*/
            for (int j = 1; j < split.size(); j++)
            {
                metro_map[i-1][j-1]=split.at(j);
            }
        }
        inFile.close();
    }
}

void MainWindow::on_routes_clicked()
{
    routes_number=1;
    QString en_s=ui->en_station_number->text();
    QString ex_s=ui->ex_station_number->text();
    int enter_station=en_s.toInt();
    int exit_station=ex_s.toInt();
    import_map();

    //qDebug()<<enter_station<<exit_station<<'\n';
    if(enter_station>=0&&enter_station<=80&&exit_station<=80&&exit_station>=0)
    {
        routes.clear();
        route.clear();
        shortest_route.clear();
        possible_routes(enter_station,exit_station,0);
        print_routes(routes);
    }
    else
    {
        QMessageBox *message=new QMessageBox();
        message->setText("StationID should between 0 and 80,please input again.");
        message->setWindowTitle("Warning");
        message->show();
    }
}


void MainWindow::on_load_data_clicked()
{
    int file_number=0;
    for(int i=0;i<211;++i)
    {
        if(file_flags[i]==1)
            file_number+=1;
    }
    if(!ui->time->isChecked()&&!ui->line_id->isChecked()&&!ui->station_id->isChecked()&&!ui->status->isChecked()&&!ui->pay_type->isChecked())
    {
        QMessageBox *message=new QMessageBox();
        message->setText("At least select one fileds.");
        message->setWindowTitle("Warning");
        message->show();
    }
    else if(count!=15895268)
    {
        QProgressDialog dialog("Loading Rate", "Cancel", 0, 24000001, this);
        dialog.setWindowTitle("Loading Data");
        dialog.setFixedSize(300,100);
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        int i=(file_number/210.00)*21000000;
        for(i; i < 24000001; i++)
        {
            dialog.setValue(i);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
                break;
            int file_number=0;
            for(int i=0;i<211;++i)
            {
                if(file_flags[i]==1)
                    file_number+=1;
            }
            if(file_number==211)
            {
                dialog.setValue(24000000);
                break;
            }
        }

    }
    file_number=0;
    for(int i=0;i<211;++i)
    {
        if(file_flags[i]==1)
            file_number+=1;
    }
    if(file_number==211)
    {
        QProgressDialog dialog("Loading Rate", "Cancel", 0, 10000, this);
        dialog.setWindowTitle("Loading Data");
        dialog.setFixedSize(300,100);
        dialog.setWindowModality(Qt::WindowModal);
        dialog.show();
        for(int i = 0; i < 10000; i++)
        {
            dialog.setValue(i);
            QCoreApplication::processEvents();
            if(dialog.wasCanceled())
                break;
        }
    }
}

void MainWindow::on_trend_clicked()
{
    int file_number=0;
    for(int i=0;i<211;++i)
    {
        if(file_flags[i]==1)
            file_number+=1;
    }
    if(file_number!=211)
    {
        QMessageBox *message=new QMessageBox();
        message->setText("Data incomplete!");
        message->setWindowTitle("Warning");
        message->show();
    }
    else
    {
        QVector<int> _count_vec0;
        QVector<int> _count_vec1;
        QVector<int> _count_vect;
        int _vec0_max=0;
        int _vec1_max=0;
        QVector<QDateTime> _time_vec0;
        QString station_id=ui->station_ID->text();
        QDateTime s_time=ui->starting_time->dateTime();
        QDateTime e_time=ui->ending_time->dateTime();
        int t_step=ui->time_step->text().toInt();
        int t_step_tosec=t_step*60;
        qDebug()<<station_id<<s_time<<e_time<<t_step;

        int span=QDateTime::fromMSecsSinceEpoch(e_time.toMSecsSinceEpoch()- s_time.toMSecsSinceEpoch()).toTime_t();


        if(station_id.toInt()>80||station_id.toInt()<0)
        {
            QMessageBox *message=new QMessageBox();
            message->setText("StationID should between 0 and 80,please input again.");
            message->setWindowTitle("Warning");
            message->show();
        }
        else if(t_step_tosec==0)
        {
            QMessageBox *message=new QMessageBox();
            message->setText("Time step should > 0,please input again.");
            message->setWindowTitle("Warning");
            message->show();
        }
        else if(span==-1)
        {
            QMessageBox *message=new QMessageBox();
            message->setText("Starting time should no later than end time,please input again.");
            message->setWindowTitle("Warning");
            message->show();
        }
        //qDebug()<<span;
        else
        {
            int points=ceil((double)span/t_step_tosec);
            qDebug()<<points;
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("dataset.db");
            db.open();
            QSqlQuery query(db);
            for(int i=0;i<points;++i)
            {
                int count=0;
                QString s_time_toqs1 =  s_time.toString("yyyy-MM-dd hh:mm:ss");
                _time_vec0.push_back(s_time);
                QString s_time_toqs2 =  s_time.addSecs(t_step_tosec).toString("yyyy-MM-dd hh:mm:ss");
                s_time=s_time.addSecs(t_step_tosec);
                QString select1="select count(*) from record where stationID = ";
                QString select2="  and time between '";
                QString select3="' and '";
                QString select4="'and status = 0";
                query.exec(select1+station_id+select2+s_time_toqs1+select3+s_time_toqs2+select4);
                //qDebug()<<select1+station_id+select2+s_time_toqs1+select3+s_time_toqs2+select4;
                while(query.next())
                {
                    count = query.value(0).toInt();
                    if(count>_vec0_max)
                        _vec0_max=count;
                    _count_vec0.push_back(count);
                }
                //qDebug()<<count;
            }
            s_time=ui->starting_time->dateTime();
            e_time=ui->ending_time->dateTime();
            for(int i=0;i<points;++i)
            {
                int count=0;
                QString s_time_toqs1 =  s_time.toString("yyyy-MM-dd hh:mm:ss");
                _time_vec0.push_back(s_time);
                QString s_time_toqs2 =  s_time.addSecs(t_step_tosec).toString("yyyy-MM-dd hh:mm:ss");
                s_time=s_time.addSecs(t_step_tosec);
                QString select1="select count(*) from record where stationID = ";
                QString select2="  and time between '";
                QString select3="' and '";
                QString select4="'and status = 1";
                query.exec(select1+station_id+select2+s_time_toqs1+select3+s_time_toqs2+select4);
                //qDebug()<<select1+station_id+select2+s_time_toqs1+select3+s_time_toqs2+select4;
                while(query.next())
                {
                    count = query.value(0).toInt();
                    if(count>_vec1_max)
                        _vec1_max=count;
                    _count_vec1.push_back(count);
                }
                //qDebug()<<count;
            }
            for(int i=0;i<points;++i)
            {
                _count_vect.push_back(_count_vec0[i]+_count_vec1[i]);
            }
            if(_count_vec0.size()>10&&_count_vec1.size()>10)
            {
                if(!ui->out_check->isChecked()&&!ui->in_check->isChecked()&&!ui->total_check->isChecked())
                {
                    QMessageBox *message=new QMessageBox();
                    message->setText("Select one trend at least.");
                    message->setWindowTitle("Warning");
                    message->show();
                }
                else{
                    QChart *chart = new QChart();
                    QLineSeries *series0 = new QLineSeries();
                    QLineSeries *series1 = new QLineSeries();
                    QLineSeries *seriest =new QLineSeries();
                    if(ui->out_check->isChecked())
                    {

                        series0->setName("Out flow");
                        for(int i=0;i<points;++i)
                        {
                            series0->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vec0[i]);
                        }
                        chart->addSeries(series0);
                    }
                    if(ui->in_check->isChecked())
                    {

                        series1->setName("In flow");
                        for(int i=0;i<points;++i)
                        {
                            series1->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vec1[i]);
                        }
                        chart->addSeries(series1);
                    }

                    if(ui->total_check->isChecked())
                    {

                        seriest->setName("Total flow");
                        for(int i=0;i<points;++i)
                        {
                            seriest->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vect[i]);
                        }
                        chart->addSeries(seriest);
                    }
                    chart->setTitle("Flow trend of station  "+station_id);

                    chart->setAnimationOptions(QChart::AllAnimations);
                    QChartView *chartview = new QChartView();
                    chartview->setRenderHint(QPainter::Antialiasing);

                    chartview->setChart(chart);
                    chartview->setWindowTitle("Flow Trend");
                    chartview->setBaseSize(1000,1000);

                    QDateTimeAxis *axisX = new QDateTimeAxis;
                    axisX->setTitleText("Time");
                    axisX->setFormat("MM-dd hh:mm");
                    axisX->setTickCount(8);
                    //    axisX->setGridLineVisible(false);

                    QValueAxis *axisY = new QValueAxis;
                    axisY->setTitleText("Number of pepople");
                    if(ui->total_check->isChecked())
                    {
                        axisY->setRange(0,_vec0_max+_vec1_max);
                    }
                    else if(_vec0_max>_vec1_max)
                        axisY->setRange(0,_vec0_max);
                    else
                        axisY->setRange(0,_vec1_max);
                    axisY->setMinorTickCount(4);
                    //    axisX->setGridLineVisible(false);

                    if(ui->total_check->isChecked())
                    {
                        chart->setAxisX(axisX, seriest);
                        chart->setAxisY(axisY, seriest);
                        chart->setAxisX(axisX, series1);
                        chart->setAxisY(axisY, series1);
                        chart->setAxisX(axisX, series0);
                        chart->setAxisY(axisY, series0);
                    }
                    else if(_vec1_max>_vec0_max)
                    {
                        chart->setAxisX(axisX, series1);
                        chart->setAxisY(axisY, series1);
                        chart->setAxisX(axisX, series0);
                        chart->setAxisY(axisY, series0);
                    }
                    else
                    {
                        chart->setAxisX(axisX, series0);
                        chart->setAxisY(axisY, series0);
                        chart->setAxisX(axisX, series1);
                        chart->setAxisY(axisY, series1);
                    }
                    chartview->show();
                }
            }
            else
            {
                if(!ui->out_check->isChecked()&&!ui->in_check->isChecked()&&!ui->total_check->isChecked())
                {
                    QMessageBox *message=new QMessageBox();
                    message->setText("Select one trend at least.");
                    message->setWindowTitle("Warning");
                    message->show();
                }
                else
                {
                    QChart *chart = new QChart();
                    QSplineSeries *series0 = new QSplineSeries();
                    QSplineSeries *series1 = new QSplineSeries();
                    QSplineSeries *seriest =new QSplineSeries();
                    if(ui->out_check->isChecked())
                    {

                        series0->setName("Out flow");
                        for(int i=0;i<points;++i)
                        {
                            series0->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vec0[i]);
                        }
                        chart->addSeries(series0);
                    }
                    if(ui->in_check->isChecked())
                    {

                        series1->setName("In flow");
                        for(int i=0;i<points;++i)
                        {
                            series1->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vec1[i]);
                        }
                        chart->addSeries(series1);
                    }

                    if(ui->total_check->isChecked())
                    {

                        seriest->setName("Total flow");
                        for(int i=0;i<points;++i)
                        {
                            seriest->append(_time_vec0[i].toMSecsSinceEpoch(),_count_vect[i]);
                        }
                        chart->addSeries(seriest);
                    }
                    chart->setTitle("Flow trend");

                    chart->setAnimationOptions(QChart::AllAnimations);
                    QChartView *chartview = new QChartView();
                    chartview->setRenderHint(QPainter::Antialiasing);

                    chartview->setChart(chart);
                    chartview->setWindowTitle("Flow Trend");
                    chartview->setBaseSize(1000,1000);

                    QDateTimeAxis *axisX = new QDateTimeAxis;
                    axisX->setTitleText("Time");
                    axisX->setFormat("MM-dd hh:mm");
                    axisX->setTickCount(8);
                    //    axisX->setGridLineVisible(false);

                    QValueAxis *axisY = new QValueAxis;
                    axisY->setTitleText("Number of people");
                    if(ui->total_check->isChecked())
                    {
                        axisY->setRange(0,_vec0_max+_vec1_max);
                    }
                    else if(_vec0_max>_vec1_max)
                        axisY->setRange(0,_vec0_max);
                    else
                        axisY->setRange(0,_vec1_max);
                    axisY->setMinorTickCount(4);
                    //    axisX->setGridLineVisible(false);

                    if(ui->total_check->isChecked())
                    {
                        chart->setAxisX(axisX, seriest);
                        chart->setAxisY(axisY, seriest);
                        chart->setAxisX(axisX, series1);
                        chart->setAxisY(axisY, series1);
                        chart->setAxisX(axisX, series0);
                        chart->setAxisY(axisY, series0);
                    }
                    else
                    {
                        if(_vec1_max>_vec0_max)
                        {
                            chart->setAxisX(axisX, series1);
                            chart->setAxisY(axisY, series1);
                            chart->setAxisX(axisX, series0);
                            chart->setAxisY(axisY, series0);
                        }
                        else
                        {
                            chart->setAxisX(axisX, series0);
                            chart->setAxisY(axisY, series0);
                            chart->setAxisX(axisX, series1);
                            chart->setAxisY(axisY, series1);
                        }
                    }

                    chartview->show();
                }
            }
        }
    }
}
