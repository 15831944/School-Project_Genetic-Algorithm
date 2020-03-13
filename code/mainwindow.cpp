#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Q3DScatter *Scatter = new Q3DScatter();
    ScatterPoints = new ScatterGraph(Scatter);
    QHBoxLayout *hLayout = new QHBoxLayout(ui->ScatterWidget);
    QWidget *container1 = QWidget::createWindowContainer(Scatter);
    hLayout->addWidget(container1, 1);
    ui->radioRiaru->setEnabled(false);
    ui->radioPaOne->setEnabled(false);
    ui->radioPaMotto->setEnabled(false);
    ui->FuncomboBox->setEnabled(false);
    ui->StartBtn->setEnabled(false);
    ui->StopBtn->setEnabled(false);
    ui->PreBtn->setEnabled(false);
    ui->NextBtn->setEnabled(false);
    ui->FirstBtn->setEnabled(false);
    ui->TheLastBtn->setEnabled(false);
    ui->Result->append("演化總代數\t最佳解");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FuncomboBox_currentIndexChanged(int index)
{
    ScatterPoints->GAmoderu->SetFuncName(index);
}

void MainWindow::on_Start_clicked()
{
    int count = ui->TrainNUM->value();
    double Avgvalue = 0.0;
    double deviation=0.0;
    double value[count];
    for(int i =0;i<count;i++){
    ScatterPoints->Clear();
    ScatterPoints->iniGAmoderu();
    ScatterPoints->RunGAmoderu();
    ui->Result->append(QString::number(ScatterPoints->GAmoderu->ShinkaNUM)+"\t"+QString::number(ScatterPoints->GAmoderu->sedai.at(ScatterPoints->GAmoderu->ShinkaNUM).theBestValue));
    Avgvalue += ScatterPoints->GAmoderu->sedai.at(ScatterPoints->GAmoderu->ShinkaNUM).theBestValue;
    value[i]=ScatterPoints->GAmoderu->sedai.at(ScatterPoints->GAmoderu->ShinkaNUM).theBestValue;
    }
    Avgvalue/=count;
    for(int i=0;i<count;i++)
       {
        deviation += pow((value[i]-Avgvalue),2.0);
       }
    deviation/=count;
    ui->Result->append("平均最佳解\t"+QString::number(Avgvalue));
    ui->Result->append("標準差\t"+QString::number(deviation));
    ui->NowShow->setText("0");

    ui->Start->setEnabled(false);
    ui->StartBtn->setEnabled(true);
    ui->StopBtn->setEnabled(true);
    ui->PreBtn->setEnabled(true);
    ui->NextBtn->setEnabled(true);
    ui->FirstBtn->setEnabled(true);
    ui->TheLastBtn->setEnabled(true);
}

void MainWindow::on_HakoSaizu_editingFinished()
{
    ScatterPoints->GAmoderu->HakoSaizu = ui->HakoSaizu->text().toInt();
}

void MainWindow::on_radioBainari_clicked()
{ScatterPoints->GAmoderu->Kodomoderu = Bainari;ui->BaiKodoBit->setEnabled(true);}

void MainWindow::on_radioRiaru_clicked()
{ScatterPoints->GAmoderu->Kodomoderu = Riaru;ui->BaiKodoBit->setEnabled(false);}

void MainWindow::on_BaiKodoBit_editingFinished()
{ScatterPoints->GAmoderu->BaiKodoBit = ui->BaiKodoBit->text().toInt();}

void MainWindow::on_radioPaOne_clicked()
{ScatterPoints->GAmoderu->Papamoderu = one;}

void MainWindow::on_radioPaTwo_clicked()
{ScatterPoints->GAmoderu->Papamoderu = two;}

void MainWindow::on_radioPaMotto_clicked()
{ScatterPoints->GAmoderu->Papamoderu = motto;}

void MainWindow::on_HeyaSaizu_editingFinished()
{ScatterPoints->GAmoderu->HeyaSaizu = ui->HeyaSaizu->text().toInt();}

void MainWindow::on_PapaChance_valueChanged(double arg1)
{ScatterPoints->GAmoderu->PapaChance = arg1;}

void MainWindow::on_TotsuhenChance_valueChanged(double arg1)
{ScatterPoints->GAmoderu->TotsuhenChance = arg1;}

void MainWindow::on_NextBtn_clicked()
{ScatterPoints->next();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));
}

void MainWindow::on_PreBtn_clicked()
{ScatterPoints->Pre();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));
}

void MainWindow::on_FirstBtn_clicked()
{ScatterPoints->TheFirst();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));
}

void MainWindow::on_TheLastBtn_clicked()
{ScatterPoints->TheLast();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));
}

void MainWindow::on_StartBtn_clicked()
{ScatterPoints->playflag = true;
 while(ScatterPoints->playflag){
    ScatterPoints->Play();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));}
}

void MainWindow::on_StopBtn_clicked()
{ScatterPoints->Stop();
 ui->NowShow->setText(QString::number(ScatterPoints->NowShow));
}
