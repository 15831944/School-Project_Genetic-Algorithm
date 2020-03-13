#ifndef GAMODEL_H
#define GAMODEL_H

#include <string>
#include <cmath>
#include <vector>
#include<QString>

using namespace std;

enum kodomoderu
{
    Bainari,
    Riaru
};
enum papamoderu
{
    one,
    two,
    motto
};
enum functionName
{
    Ackley,
    Rastrigin,
    Rosenbrock,
    Schwefel
};

class AckleyFunc
{
public:
    double min,max;
    double Value(double x,double y,double z);
};



class Menba
{
public:
    QString PosX,PosY,PosZ;
    double Value;
    int age;
};

class Sedai
{
public:
    vector<Menba>menba;
    vector<int>Heya;
    double theBestValue;
};


class GAmodel{

public:
    GAmodel();
    int HakoSaizu;
    kodomoderu Kodomoderu;
    papamoderu Papamoderu;
    functionName FuncName;
    AckleyFunc Ackleyfunc;
    int BaiKodoBit;
    int HeyaSaizu;
    double PapaChance;
    double TotsuhenChance;
    int TotsuhenChanceNUM;
    int TotsuhenChancePOW;
    vector<Sedai>sedai;
    void ShokkaGA(int Hakosaizu,int Baikodobit,functionName Funcname);
    void ShokkaGA(int Hakosaizu,functionName Funcname);
    int KeisanBit(int Baikodobit,int Max,int Min);
    QString DoBainariKodo(int bit);
    double DeBainariKodo(QString bainari,int Max,int Min);
    int Partition(double *arr,int *flag, int front, int end);
    void QuickSort(double *arr, int *flag, int front, int end);
    int ShinkaNUM;
    void Shinka(int now,functionName FuncName);
    void FindPapaMenba(int now);
    void Copy2Heya(int now,int flag);
    void CalTotsuhenNUM();
    QString Totsuhen(QString BaiKodo);
    void Papa(int now,functionName FuncName);
    void SetFuncName(int flag);

};


#endif // GAMODEL_H
