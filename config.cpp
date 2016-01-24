#include "config.h"
#include "ui_config.h"
#include<QFile>
#include<stdio.h>
#include"widget.h"

config::config(Widget *m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
    main = m;
    char buf[100];
    FILE*fp = fopen("./config.txt","r+");
    if(!fp){
        qDebug()<<"open failed";
        fclose(fp);
         this->exec();
    }
    if(fgets(buf,sizeof(buf),fp)){
      buf[strlen(buf)-1] = '\0';
      ui->ip->setText(buf);
    }
    if(fgets(buf,sizeof(buf),fp)){
         buf[strlen(buf)-1] = '\0';
      ui->port->setText(buf);
    }
    if(fgets(buf,sizeof(buf),fp)){
         buf[strlen(buf)-1] = '\0';
      ui->vport->setText(buf);
    }
    if(fgets(buf,sizeof(buf),fp)){
         buf[strlen(buf)-1] = '\0';
      ui->id->setText(buf);
    }
    if(fgets(buf,sizeof(buf),fp)){
         buf[strlen(buf)-1] = '\0';
      ui->poss->setText(buf);
    }

    fclose(fp);



    this->exec();

}

config::~config()
{
    delete ui;
}

void config::on_pushButton_clicked()
{
  main->ip = ui->ip->text();
   main->port = ui->port->text();
   main->id = ui->id->text();
    main->vport = ui->vport->text();
    main->poss = ui->poss->text();
    FILE*fp = fopen("./config.txt","w");
    if(!fp){
        qDebug()<<"open config file error";
    }
    fprintf(fp,"%s\n%s\n%s\n%s\n%s\n",ui->ip->text().toStdString().c_str(),ui->port->text().toStdString().c_str(),ui->vport->text().toStdString().c_str(),ui->id->text().toStdString().c_str(),ui->poss->text().toStdString().c_str());

    fclose(fp);
    this->close();

}
