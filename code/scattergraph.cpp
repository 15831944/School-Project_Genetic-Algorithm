#include <scattergraph.h>
#include <qscatterdataproxy.h>
#include <qvalue3daxis.h>
#include <q3dscene.h>
#include <qscatter3dseries.h>
#include <q3dtheme.h>
#include <qmath.h>
#include <cstdlib>
#include <iostream>
#include <QTime>
#include <time.h>
#include <QCoreApplication>
#include <cstdlib>
#include <QFile>

#define RND() ((double)rand()/RAND_MAX)

using namespace std;
using namespace QtDataVisualization;

ScatterGraph::ScatterGraph(Q3DScatter *scatter)
    : m_graph(scatter)
{
    GAmoderu = new GAmodel();
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(80.0f);
    m_graph->activeTheme()->setFont(font);
    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(-32.0f, 32.0f);
    m_graph->axisY()->setRange(-32.0f, 32.0f);
    m_graph->axisZ()->setRange(-32.0f, 32.0f);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);
    proxy     = new QScatterDataProxy();
    series    = new QScatter3DSeries(proxy);
    dataArray = new QScatterDataArray();
    m_graph->addSeries(series);

    GAmoderu->HakoSaizu = 50;
    GAmoderu->Kodomoderu = Bainari;
    GAmoderu->Papamoderu = two;
    GAmoderu->HeyaSaizu = 40;
    GAmoderu->BaiKodoBit = 3;
    GAmoderu->PapaChance = 1.0;
    GAmoderu->TotsuhenChance = 0.5;
    GAmoderu->ShinkaNUM = 0;
    NowShow = 0;
    playflag = false;
}



ScatterGraph::~ScatterGraph()
{
    delete m_graph;
}

void ScatterGraph::iniGAmoderu()
{
    cout << "Moderu Info."     <<endl
         << "Function Flag : " << GAmoderu->FuncName <<endl
         << "HakoSaizu : "     << GAmoderu->HakoSaizu <<endl
         << "Kodomoderu : "    << GAmoderu->Kodomoderu <<endl
         << "Using Bit : "     << GAmoderu->BaiKodoBit <<endl
         << "Papamoderu : "    << GAmoderu->Papamoderu <<endl
         << "HeyaSaizu : "     << GAmoderu->HeyaSaizu <<endl
         << "PapaChance : "    << GAmoderu->PapaChance<<endl
         << "TotsuhenChance : "<< GAmoderu->TotsuhenChance<<endl;
    if(GAmoderu->Kodomoderu == Bainari)
      {GAmoderu->ShokkaGA(GAmoderu->HakoSaizu,GAmoderu->BaiKodoBit,GAmoderu->FuncName);
       GAmoderu->Shinka(GAmoderu->ShinkaNUM,GAmoderu->FuncName);
       addData(0);
      }

}

void ScatterGraph::RunGAmoderu()
{
    int SameFlag = 0;
    while(SameFlag<150)
       {
        if(GAmoderu->sedai.at(GAmoderu->ShinkaNUM).theBestValue == GAmoderu->sedai.at(GAmoderu->ShinkaNUM-1).theBestValue)
        {SameFlag++;}
        else
        {SameFlag=0;}
        GAmoderu->Shinka(GAmoderu->ShinkaNUM,GAmoderu->FuncName);
       }

    /*for(int i =0;i<500;i++)
       {
        GAmoderu.Shinka(GAmoderu.ShinkaNUM,GAmoderu.FuncName);
       }*/

}
void ScatterGraph::addData(int NUM)
{
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");

    int ParticalSize = GAmoderu->HakoSaizu;
    dataArray->resize(ParticalSize);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    for (int i = 0; i < GAmoderu->sedai.at(NUM).menba.size(); i++)
        {float x;
         float y;
         float z;
         switch (GAmoderu->FuncName)
         {
          case 0:
              x = (float)GAmoderu->DeBainariKodo(GAmoderu->sedai.at(NUM).menba.at(i).PosX,GAmoderu->Ackleyfunc.max,GAmoderu->Ackleyfunc.min);
              y = (float)GAmoderu->DeBainariKodo(GAmoderu->sedai.at(NUM).menba.at(i).PosY,GAmoderu->Ackleyfunc.max,GAmoderu->Ackleyfunc.min);
              z = (float)GAmoderu->DeBainariKodo(GAmoderu->sedai.at(NUM).menba.at(i).PosZ,GAmoderu->Ackleyfunc.max,GAmoderu->Ackleyfunc.min);
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

            ptrToDataArray->setPosition(QVector3D(x,z,y));
            ptrToDataArray++;

    }
    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    if (m_graph->seriesList().size())
        m_graph->seriesList().at(0)->setMesh(QAbstract3DSeries::MeshPoint);
    cout << GAmoderu->sedai.at(NUM).theBestValue <<endl;
}
void ScatterGraph::next()
{
    if((NowShow+1)<GAmoderu->sedai.size())
      { NowShow++;
        addData(NowShow);}
}

void ScatterGraph::Pre()
{
    if((NowShow-1)>0)
      { NowShow--;
        addData(NowShow);}
}

void ScatterGraph::TheFirst()
{
    NowShow=0;
    addData(NowShow);
}

void ScatterGraph::TheLast()
{
    NowShow = GAmoderu->sedai.size()-1;
    addData(NowShow);
}

void ScatterGraph::Play()
{   next();
    QTime dieTime= QTime::currentTime().addMSecs(200);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void ScatterGraph::Stop()
{addData(NowShow);playflag = false;

}

void ScatterGraph::Clear()
{
    temp.Ackleyfunc = GAmoderu->Ackleyfunc;
    temp.BaiKodoBit = GAmoderu->BaiKodoBit;
    temp.FuncName = GAmoderu->FuncName;
    temp.HakoSaizu=GAmoderu->HakoSaizu;
    temp.HeyaSaizu=GAmoderu->HeyaSaizu;
    temp.Kodomoderu = GAmoderu->Kodomoderu;
    temp.PapaChance = GAmoderu->PapaChance;
    temp.Papamoderu = GAmoderu->Papamoderu;
    temp.TotsuhenChance = GAmoderu->TotsuhenChance;

    delete GAmoderu;

    GAmoderu = new GAmodel();

    GAmoderu->Ackleyfunc = temp.Ackleyfunc ;
    GAmoderu->BaiKodoBit = temp.BaiKodoBit ;
    GAmoderu->FuncName   = temp.FuncName ;
    GAmoderu->HakoSaizu  = temp.HakoSaizu;
    GAmoderu->HeyaSaizu  = temp.HeyaSaizu;
    GAmoderu->Kodomoderu = temp.Kodomoderu;
    GAmoderu->PapaChance = temp.PapaChance;
    GAmoderu->Papamoderu = temp.Papamoderu;
    GAmoderu->TotsuhenChance = temp.TotsuhenChance;
}




