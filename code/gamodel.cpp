#include "gamodel.h"
#define PI 3.14159265359
#include <iostream>
#include <QString>
#define RND() ((double)rand()/RAND_MAX)

using namespace std;

GAmodel::GAmodel()
{
    HakoSaizu  = 50;
    Kodomoderu = Bainari;
    Papamoderu = two;
    HeyaSaizu  = 40;
    BaiKodoBit = 1;
    FuncName   = Ackley;
    Ackleyfunc.min = -32;
    Ackleyfunc.max = 32;
    TotsuhenChanceNUM = 0;
    TotsuhenChancePOW = 0;
    ShinkaNUM = 0;

}

void GAmodel::ShokkaGA(int Hakosaizu, int Baikodobit,functionName Funcname)
{
    cout << "Run ShokkaGA - Bainari mode" <<endl;
    Sedai Temp_Saidai;
    Temp_Saidai.theBestValue = 0;
    sedai.push_back(Temp_Saidai);
    int _Hakosaizu = Hakosaizu;
    int _Baikodobit= Baikodobit;
    int Min,Max;
    CalTotsuhenNUM();
    switch (Funcname) {
    case 0:
        Min = Ackleyfunc.min;
        Max = Ackleyfunc.max;
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    default:
        break;
    }
    int bit = KeisanBit(_Baikodobit,Max,Min);



    for(int i=0;i<_Hakosaizu;i++)
       {
        QString PosX = DoBainariKodo(bit);
        QString PosY = DoBainariKodo(bit);
        QString PosZ = DoBainariKodo(bit);
        Menba menba;
        menba.PosX = PosX;
        menba.PosY = PosY;
        menba.PosZ = PosZ;
        switch (Funcname) {
        case 0:
            menba.Value = Ackleyfunc.Value(DeBainariKodo(PosX,Max,Min),DeBainariKodo(PosY,Max,Min),DeBainariKodo(PosZ,Max,Min));
            if(i==1 || menba.Value<sedai.at(0).theBestValue)
            {sedai.at(0).theBestValue = menba.Value;}
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        default:
            break;
        }
        menba.age = 0;
        sedai.at(0).menba.push_back(menba);
       }
}

void GAmodel::ShokkaGA(int Hakosaizu,functionName Funcname)
{
    cout << "Run ShokkaGA - Riaru mode" <<endl;
    Sedai Temp_Saidai;
    sedai.push_back(Temp_Saidai);
    int _Hakosaizu = Hakosaizu;
}

int GAmodel::KeisanBit(int Baikodobit,int Max,int Min)
{
    double Seido = 1/pow(10.0,(double)Baikodobit);
    int bit = 1;
    while(pow(2,(double)bit)*Seido<=(Max-Min)){bit++;}
    return bit;
}

QString GAmodel::DoBainariKodo(int bit)
{
 int maxBaiNUM = pow(2.0,(double)bit);
 int DeNUM = rand() % maxBaiNUM;
 QString Bainari = QString::number(DeNUM,2);
 Bainari = Bainari.rightJustified(bit,'0');
 return Bainari;
}

double GAmodel::DeBainariKodo(QString bainari,int Max,int Min)
{
 int val = 0;
 int bit = bainari.length();
 for( int i = 0; i < bit; i++ ) {
     val = (val << 1) + bainari.at(i).digitValue();
    }
 double value;
 value = (val-0)/(pow(2,(double)bit)-0)*(Max-Min)+(Min);
 return value;
}

int GAmodel::Partition(double *arr, int *flag, int front, int end)
{
    double TempD;
    int TempI;
    double pivot = arr[end];
       int i = front -1;
       for (int j = front; j < end; j++) {
           if (arr[j] < pivot) {
               i++;

               TempD = arr[i];
               arr[i] = arr[j];
               arr[j] = TempD;

               TempI = flag[i];
               flag[i] = flag[j];
               flag[j] = TempI;
               //swap(&arr[i], &arr[j]);
           }
       }
       i++;
       TempD = arr[i];
       arr[i] = arr[end];
       arr[end] = TempD;

       TempI = flag[i];
       flag[i] = flag[end];
       flag[end] = TempI;
       //swap(&arr[i], &arr[end]);
       return i;
}

void GAmodel::QuickSort(double *arr, int *flag, int front, int end)
{
    if (front < end) {
           int pivot = Partition(arr,flag, front, end);
           QuickSort(arr,flag, front, pivot - 1);
           QuickSort(arr,flag, pivot + 1, end);
       }
}

void GAmodel::Shinka(int now,functionName FuncName)
{
    FindPapaMenba(now);
    Papa(now,FuncName);
}

void GAmodel::FindPapaMenba(int now)
{
    int MenbaSaisu =  sedai.at(now).menba.size() ;
    double MenbaTotal = 0.0;
    int FitnessTotal = 0;
    double MenbaValue[MenbaSaisu];
    int MenbaFlag[MenbaSaisu];
    for(int i = 0;i<MenbaSaisu;i++)//讀入當代成員數據
       {
        MenbaValue[i] = sedai.at(now).menba.at(i).Value;
        MenbaFlag[i] = i;
       }
    QuickSort(MenbaValue,MenbaFlag,0,MenbaSaisu-1);
    for(int i = 0;i<MenbaSaisu;i++)//修改適應值
       {
        MenbaValue[i] = MenbaValue[MenbaSaisu-1]-MenbaValue[i];
        MenbaTotal += MenbaValue[i];
       }
    for(int i = 0;i<MenbaSaisu;i++)//計算複製數量判斷值
       {
        MenbaValue[i] = (int)(MenbaValue[i]/MenbaTotal*MenbaSaisu+0.5);
        FitnessTotal += (int)MenbaValue[i];
       }
    for(int i = 0;i<MenbaSaisu;i++)//計算複製數量
       {
        MenbaValue[i] = (int)(MenbaValue[i]/FitnessTotal*HeyaSaizu+0.5);
        //cout <<  MenbaValue[i] << "   "  << MenbaFlag[i] <<endl;
       }
    int HeyaUsed=0;
    for(int i =0;i<MenbaSaisu;i++)
       {
        for(int j = 0;j<MenbaValue[i];j++)
           {if(HeyaUsed>HeyaSaizu-1){break;}
            Copy2Heya(now,MenbaFlag[i]);
            HeyaUsed++;
           }
        if(HeyaUsed>HeyaSaizu){break;}
       }
    if(HeyaUsed<HeyaSaizu)
      {
        for(int i = 0;i<(HeyaSaizu-HeyaUsed);i++)
           {Copy2Heya(now,MenbaFlag[i]);}
      }
}

void GAmodel::Copy2Heya(int now,int flag)
{
    sedai.at(now).Heya.push_back(flag);
}

void GAmodel::CalTotsuhenNUM()
{
    double chance = TotsuhenChance;
    int posNUM=1;
    while((int)(chance*pow(10,(double)posNUM))==0)
         {posNUM++;}
    TotsuhenChanceNUM = chance*pow(10,(double)posNUM);
    TotsuhenChancePOW = pow(10,(double)posNUM);
}

QString GAmodel::Totsuhen(QString BaiKodo)
{
    int roll =rand() % TotsuhenChancePOW;
    for(int i = 0;i<TotsuhenChanceNUM;i++)
       {
        int Temp =  rand() % TotsuhenChancePOW;
        if(Temp == roll)
          {
           int TotsuhenPNUM = (rand()%BaiKodo.length())+1;
           for(int j=0;j<TotsuhenPNUM;j++)
              {
               int TotsuhenP = rand()%(BaiKodo.length()-1);
               if(BaiKodo[TotsuhenP]=='1'){BaiKodo[TotsuhenP]='0';}
               else                       {BaiKodo[TotsuhenP]='1';}
              }
          }
       }
    return BaiKodo;
}

void GAmodel::Papa(int now,functionName FuncName)
{
    vector<Menba>NewMenba;
    for(int i=0;i<(int)(sedai.at(now).Heya.size()/2);i++)
       {int Pa1 = rand() % ((int)(sedai.at(now).Heya.size())-1);
        int Pa2 = rand() % ((int)(sedai.at(now).Heya.size())-1);
        switch (Papamoderu) {
        case 0:

            break;
        case 1:
            {
            int bit = sedai.at(now).menba.at(0).PosX.length();
            int midbit = (int)(bit/2);
            int Change1 = rand() % midbit ;
            int Change2 = rand() % (bit-midbit) + midbit;
            QString First,Second;
            QString Middle1,Middle2;
            QString Temp;
            Menba menba1,menba2;

            First  = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa1)).PosX;
            Second = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa2)).PosX;

            Middle1 = First.mid(Change1,Change2-Change1-1);
            Middle2 = Second.mid(Change1,Change2-Change1-1);
            First.replace(Change1,Change2-Change1-1,Middle2);
            Second.replace(Change1,Change2-Change1-1,Middle1);

            Temp = Totsuhen(First);
            First.clear();
            First = Temp;
            Temp.clear();

            Temp = Totsuhen(Second);
            Second.clear();
            Second = Temp;
            Temp.clear();

            menba1.PosX = First;
            menba2.PosX = Second;

            First.clear();Second.clear();Middle1.clear();Middle2.clear();//清除QString

            First  = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa1)).PosY;
            Second = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa2)).PosY;

            Change1 = rand() % midbit ;
            Change2 = rand() % (bit-midbit) + midbit;

            Middle1 = First.mid(Change1,Change2-Change1-1);
            Middle2 = Second.mid(Change1,Change2-Change1-1);
            First.replace(Change1,Change2-Change1-1,Middle2);
            Second.replace(Change1,Change2-Change1-1,Middle1);

            Temp = Totsuhen(First);
            First.clear();
            First = Temp;
            Temp.clear();

            Temp = Totsuhen(Second);
            Second.clear();
            Second = Temp;
            Temp.clear();

            menba1.PosY = First;
            menba2.PosY = Second;

            First.clear();Second.clear();Middle1.clear();Middle2.clear();//清除QString

            First  = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa1)).PosZ;
            Second = sedai.at(now).menba.at(sedai.at(now).Heya.at(Pa2)).PosZ;

            Change1 = rand() % midbit ;
            Change2 = rand() % (bit-midbit) + midbit;

            Middle1 = First.mid(Change1,Change2-Change1-1);
            Middle2 = Second.mid(Change1,Change2-Change1-1);
            First.replace(Change1,Change2-Change1-1,Middle2);
            Second.replace(Change1,Change2-Change1-1,Middle1);

            Temp = Totsuhen(First);
            First.clear();
            First = Temp;
            Temp.clear();

            Temp = Totsuhen(Second);
            Second.clear();
            Second = Temp;
            Temp.clear();

            menba1.PosZ = First;
            menba2.PosZ = Second;

            switch (FuncName) {
            case 0:
                menba1.Value = Ackleyfunc.Value(DeBainariKodo(menba1.PosX,Ackleyfunc.max,Ackleyfunc.min),
                                                DeBainariKodo(menba1.PosY,Ackleyfunc.max,Ackleyfunc.min),
                                                DeBainariKodo(menba1.PosZ,Ackleyfunc.max,Ackleyfunc.min));
                menba1.age = 0;

                menba2.Value = Ackleyfunc.Value(DeBainariKodo(menba2.PosX,Ackleyfunc.max,Ackleyfunc.min),
                                                DeBainariKodo(menba2.PosY,Ackleyfunc.max,Ackleyfunc.min),
                                                DeBainariKodo(menba2.PosZ,Ackleyfunc.max,Ackleyfunc.min));
                menba2.age = 0;
                NewMenba.push_back(menba1);
                NewMenba.push_back(menba2);
                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            default:
                break;
            }
            break;}
        case 2:

            break;
        default:
            break;
        }
       }

    double NewMenbaValue[NewMenba.size()];
    int NewMenbaFlag[NewMenba.size()];
    for(int i=0;i<NewMenba.size();i++)
       {
        NewMenbaValue[i] = NewMenba.at(i).Value;
        NewMenbaFlag[i]=i;;
       }
    QuickSort(NewMenbaValue,NewMenbaFlag,0,NewMenba.size()-1);
    double MenbaValue[sedai.at(now).menba.size()];
    int MenbaFlag[sedai.at(now).menba.size()];
    for(int i = 0;i<sedai.at(now).menba.size();i++)
       {
        MenbaValue[i] = sedai.at(now).menba.at(i).Value;
        MenbaFlag[i] = i;
        sedai.at(now).menba.at(i).age++;
       }
    QuickSort(MenbaValue,MenbaFlag,0,sedai.at(now).menba.size()-1);
    Sedai SedaiTemp;
    sedai.push_back(SedaiTemp);
    for(int i =0;i<NewMenba.size()-(NewMenba.size()/2);i++)
       {sedai.at(now+1).menba.push_back(NewMenba.at(NewMenbaFlag[i]));}
    for(int i =0;i<sedai.at(now).menba.size()-(NewMenba.size()/2);i++)
       {sedai.at(now+1).menba.push_back(sedai.at(now).menba.at(MenbaFlag[i]));}

    if(sedai.at(now).menba.at(MenbaFlag[0]).Value<NewMenba.at(NewMenbaFlag[0]).Value)//找出theBestValue
      {sedai.at(now+1).theBestValue = sedai.at(now).menba.at(MenbaFlag[0]).Value;}
    else
      {sedai.at(now+1).theBestValue = NewMenba.at(NewMenbaFlag[0]).Value;}

    ShinkaNUM++;
}

void GAmodel::SetFuncName(int flag)
{
    switch (flag) {
    case 0:
        FuncName = Ackley;
        break;
    case 1:
        FuncName = Rastrigin;
        break;
    case 2:
        FuncName = Rosenbrock;
        break;
    case 3:
        FuncName = Schwefel;
        break;
    default:
        break;
    }
}

double AckleyFunc::Value(double x, double y, double z)
{
    return -20*exp(-0.2*sqrt((x*x+y*y+z*z)/3))-exp((cos(2*PI*x)+cos(2*PI*y)+cos(2*PI*z))/3)+exp(1)+20 ;
}
