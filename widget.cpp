#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btn_getJson,&QPushButton::clicked,this,[=](){
        QJsonObject rootObj ;
        rootObj.insert("name","china");

        QJsonObject infoObj ;
        infoObj.insert("capital","NanChang");
        infoObj.insert("asian",true);
        infoObj.insert("founded",1949);
        rootObj.insert("info",infoObj);

        QJsonArray provinces;
        QJsonObject shanDongObj ;
        QJsonObject zheJiangObj ;
        shanDongObj.insert("name","ShanDong");
        shanDongObj.insert("capital","JiNan");
        zheJiangObj.insert("name","ZheJiang");
        zheJiangObj.insert("capital","HangZhou");
        provinces.append(shanDongObj);
        provinces.append(zheJiangObj);
        rootObj.insert("provinces",provinces);

        QJsonDocument doc(rootObj);
        json = doc.toJson();

        ui->plainTextEdit->appendPlainText(json);
    });

    connect(ui->btn_save,&QPushButton::clicked,this,[=](){
        if(ui->plainTextEdit->toPlainText()==nullptr)
            return;

        QFile file = QFileDialog::getSaveFileName(this);
        if(!file.open(QIODevice::WriteOnly)){
            qDebug()<<"文件打开失败";
            return;
        }

        file.write(json);
        file.close();
    });

    connect(ui->btn_saveJson,&QPushButton::clicked,this,[=](){
        ui->plainTextEdit->clear();
        QFile file(":/cityjson.txt");
        if(!file.open(QIODevice::ReadOnly)){
            qDebug()<<"文件打开失败";
            return;
        }
        QByteArray json = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(json);
        if(!doc.isObject()){
            qDebug()<<"error! the file is not a json!";
            return;
        }

        QJsonObject jsonData = doc.object();  //获得json对象
        QStringList keys = jsonData.keys();
        for(int i = 0;i<jsonData.size();i++){
            QString key = keys[i];
            //qDebug()<<key<<":";
            QJsonValue value = jsonData.value(key);
            if(value.isBool()){
                qDebug()<<key<<":bool:"<<value.toBool();
            }
            else if(value.isString()){
                qDebug()<<"执行QString";
                qDebug()<<key<<":"<<value.toString();
            }
            else if(value.isObject()){
                QJsonObject info = value.toObject();
                bool asian = info["asian"].toBool();
                QString capital = info["capital"].toString();
                int year = info["founded"].toInt();
                qDebug()<<"asian"<<":"<<asian;
                qDebug()<<"capital"<<":"<<capital;
                qDebug()<<"founded"<<":"<<year;
            }
            else if(value.isArray()){
                QJsonArray provinces = value.toArray();
                for(int j = 0;j<provinces.size();j++){
                    QJsonObject city = provinces[j].toObject();
                    QString capital = city["capital"].toString();
                    QString name = city["name"].toString();
                    qDebug()<<"name"<<":"<<name;
                    qDebug()<<"capital"<<":"<<capital;
                }
            }
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

