#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include "nfadfa.h"
#include "compress.h"
#include <QDir>
#include <QFileInfo>
#include<QCoreApplication>
#include<QProcess>
#include<QString>
#include<QDebug>
#include <QPixmap>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int chars(string s)
{
    int n=0;
    for(int i=0; i<int(s.size());i++)
    {
        if((s[i]>=47 && s[i]<=90)||(s[i]>=95 && s[i]<=122)||s[i]==123||s[i]==125||s[i]==33||s[i]==44)
            n++;
    }
    return n;
}

void MainWindow::on_Button1_clicked()
{
    ui->label_3->clear();
    nfadfa NFA;
    string zzz;
    QString text = ui->textEdit->toPlainText();
    string s = text.toStdString();
    //将正则表达式转化为nfa
    s = NFA.insert_concat(s);
    s = NFA.regexp_to_postfix(s);
    NFA.postfix_to_nfa(s);
    //将nfa转化为dfa
    set<int> si;
    NFA.nfa_to_dfa(si);
    //最小化dfa
    NFA.minimize_dfa();

    QString z = QCoreApplication::applicationDirPath();
    zzz = z.toStdString();

    NFA.show_nfa(zzz);
    NFA.show_dfa(zzz);
    NFA.show_mini_dfa(zzz);
    NFA.show_code(zzz);
    QMessageBox::information(this, "确认信息", "转换完成！");


}

void MainWindow::on_Button2_clicked()
{
    //创建进程执行命令，根据dot.txt文件画出png图并保存在其目录下
    system("dot -Tpng ./debug/graph/nfa.dot -o ./debug/graph/nfa.png");
    //将生成的nfa图展示出来
    QPixmap image;
    image.load("./debug/graph/nfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->setScaledContents(true);
    ui->label_3->show();

}

void MainWindow::on_Button3_clicked()
{
    system("dot -Tpng ./debug/graph/dfa.dot -o ./debug/graph/dfa.png");
    //将生成的dfa图展示出来
    QPixmap image;
    image.load("./debug/graph/dfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->setScaledContents(true);
    ui->label_3->show();

}

void MainWindow::on_Button4_clicked()
{
     system("dot -Tpng ./debug/graph/mini_dfa.dot -o ./debug/graph/mini_dfa.png");
    //将生成的dfa图展示出来
    QPixmap image;
    image.load("./debug/graph/mini_dfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->setScaledContents(true);
    ui->label_3->show();
}

void MainWindow::on_Button4_2_clicked()
{
    ifstream in("compress.h");
    string content;
    ui->textBrowser->clear();
    while (getline (in, content))
    {
        QString  content_1=QString::fromStdString(content);
        ui->textBrowser->append(content_1);
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(
                this, tr("open image file"),
                "./", tr("Txt files(*.txt);;All files (*.*)"));
    string filepath = file.toStdString();
    cout<<filepath<<endl;
    string content;
    ifstream in(filepath);
    if(in)
    {
        ui->textEdit->clear();
        while (getline (in, content))
        {
            QString  content_1=QString::fromStdString(content);
            ui->textEdit->append(content_1);
        }
    }
    else{
        cout<<"error";
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ofstream out("re.txt");
    QString text = ui->textEdit->toPlainText();
    string s = text.toStdString();
    out<<s;
    out.close();
    QMessageBox::information(this, "确认信息", "词法分析程序compress.h生成");

}
void MainWindow:: on_Button5_clicked()
{
    string INPUT_PATH = "SAMPLE.TNY";
    Code(INPUT_PATH);
    displayCode(match);
    ifstream in("sample.lex");
    string content;
    ui->textBrowser_2->clear();
    while (getline (in, content))
    {
        QString  content_1=QString::fromStdString(content);
        ui->textBrowser_2->append(content_1);
    }
    in.close();

    ifstream infile("codeTiny.txt");
    string content1;
    ui->textBrowser_3->clear();
    while (getline (infile, content1))
    {
        QString  content_2=QString::fromStdString(content1);
        ui->textBrowser_3->append(content_2);
    }
    infile.close();

    QMessageBox::information(this, "确认信息", "编码结果保存至sample.lex");

}








