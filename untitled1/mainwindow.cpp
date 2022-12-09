#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<myfunctions.h>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect函数
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(start()));
}
struct value2{
    QString name,time,w;
};
struct value3{
    string name;
    int year,month,day;
    int w;
};//存于链表中
void bridge(vector<value2> &tofill,bptr rootptr)
{
    if(rootptr==NULL)return ;
   bridge(tofill,rootptr->lch);

   value2 temp;

   temp.name=StringToQString(rootptr->v.name);
   temp.time=StringToQString(rootptr->v.time);
   temp.w=StringToQString(IntToString(rootptr->v.w));

   tofill.push_back(temp);

   bridge(tofill,rootptr->rch);
}
void MainWindow::start()
{
    AVL myavl;
    ui->textBrowser_4->clear();
    ui->textBrowser_5->clear();
    ui->textBrowser_6->clear();

    QString content = ui->textEdit->toPlainText();
    string content_char = content.toLatin1().data(); // 将QString转化为char字符数组
    QString result;
    value2 myvalue;
    vector<value2>output;
    int cnt=0;
    for(int i=0;i<content_char.size();++i)
    {
        if(content_char[i]=='\n'){
            cnt++;
            continue;
        }
        else if(cnt==0)myvalue.name=myvalue.name+content_char[i];
        else if(cnt==1)myvalue.time=myvalue.time+content_char[i];
        else myvalue.w=myvalue.w+content_char[i];
    }

    value avlvalue;
    value3 listvalue;
    bptr Root=myavl.Root;

    avlvalue.name=QStringToString(myvalue.name);
    avlvalue.time=QStringToString(myvalue.time);
    avlvalue.w=StringToInt(QStringToString(myvalue.w));

    myavl.treeInsert(Root,avlvalue);
    myavl.browse(Root);

    bridge(output,Root);//得到了中序遍历QString输出
    for(int i=0;i<output.size();++i)
    {
       ui->textBrowser_4->append(output[i].name);

       ui->textBrowser_5->append(output[i].time);

       ui->textBrowser_6->append(output[i].w);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
