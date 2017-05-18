#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <QString>
#include <QVector>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(720, 480));
    readFromFile();
    ui->cntLabel->setText(QString::number(ui->listWidget->count()));
}

MainWindow::~MainWindow()
{
    printOnFile();
    delete ui;
}

void MainWindow::on_addBtn_clicked()
{
    if(ui->textEdit->toPlainText().length() == 0){
        ui->errorLabel_2->setText("Введите вопрос");
        return;
    }
    ui->listWidget->addItem(ui->textEdit->toPlainText());
    ui->textEdit->clear();
    ui->cntLabel->setText(QString::number(ui->listWidget->count()));
    ui->errorLabel_2->setText("");
    ui->errorLabel->setText("");
}

void MainWindow::on_delBtn_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
    ui->cntLabel->setText(QString::number(ui->listWidget->count()));
    ui->errorLabel_2->setText("");
    ui->errorLabel->setText("");
}

void MainWindow::printOnFile(){
    freopen("/home/bn/questions.txt", "w", stdout);
    for(int i = 0; i < ui->listWidget->count(); i++){
        string txt = QString(ui->listWidget->item(i)->text()).toStdString();
        cout << txt << endl;
    }
    fclose(stdout);
}

void MainWindow::readFromFile(){
    freopen("/home/bn/questions.txt", "r", stdin);
    string question;
    while(getline(cin, question)){
        if(!question.empty()){
            ui->listWidget->addItem(QString::fromStdString(question));
        }
    }
    fclose(stdin);
}

long long rdtsc(){
    long long x;
    asm("rdtsc" : "=A"(x));
    return x;
}

void MainWindow::on_generateBt_clicked()
{
    QString txt = ui->cntEdit->toPlainText();
    bool ok = true;
    for(int i = 0; i < txt.length(); i++){
        if(!txt[i].isDigit()){
            ok = false;
            break;
        }
    }

    if(!ok || txt.length() == 0){
        ui->errorLabel->setText("Введите число");
        return;
    }

    vector<QString> questions;
    int n = ui->cntEdit->toPlainText().toInt();
    for(int i = 0; i < ui->listWidget->count(); i++){
        questions.push_back(ui->listWidget->item(i)->text());
    }
    if(questions.size() % n != 0){
           ui->errorLabel_2->setText("");
           ui->errorLabel->setText("Количество вопросов не кратно количеству вопросов в одном экзаменнационном билете");
    } else {
        int tickets = (int)questions.size() / n;
        cerr << "Number of tickets: " << tickets << endl;
        srand(rdtsc());
        freopen("/home/bn/generated.txt", "w", stdout);
        for(int i = 1; di <= tickets; i++){
            cout << "Билет № " << i << '\n';
            for(int j = 1; j <= n; j++){
                int rand_ind = rand() % (int)questions.size();
                string cur_question = questions[rand_ind].toStdString();
                cout << cur_question << '\n';
                questions.erase(questions.begin() + rand_ind);
            }
            cout << '\n';
        }
        fclose(stdout);
        ui->errorLabel_2->setText("Билеты были сгенерированы, перейдите к файлу ...");
    }
    // need to be tested

}
