#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Q3DScatter>
#include <scattergraph.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ScatterGraph *ScatterPoints;
private slots:
   void on_FuncomboBox_currentIndexChanged(int index);

   void on_Start_clicked();

   void on_HakoSaizu_editingFinished();

   void on_radioBainari_clicked();

   void on_radioRiaru_clicked();

   void on_BaiKodoBit_editingFinished();

   void on_radioPaOne_clicked();

   void on_radioPaTwo_clicked();

   void on_radioPaMotto_clicked();

   void on_HeyaSaizu_editingFinished();

   void on_PapaChance_valueChanged(double arg1);

   void on_TotsuhenChance_valueChanged(double arg1);

   void on_NextBtn_clicked();

   void on_PreBtn_clicked();

   void on_FirstBtn_clicked();

   void on_TheLastBtn_clicked();

   void on_StartBtn_clicked();

   void on_StopBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
