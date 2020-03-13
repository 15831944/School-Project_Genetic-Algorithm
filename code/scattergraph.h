#ifndef SCATTERGRAPH_H
#define SCATTERGRAPH_H


#include <qscatter3dseries.h>
#include <qscatterdataproxy.h>
#include <Qfont>
#include <QLabel>
#include "gamodel.h"
#include <Q3DScatter>

using namespace QtDataVisualization;

class ScatterGraph : public QObject
{
    Q_OBJECT
public:
    explicit ScatterGraph(Q3DScatter *scatter);
    ~ScatterGraph();
    GAmodel *GAmoderu;
    GAmodel temp;
    void iniGAmoderu();
    void RunGAmoderu();
    void addData(int NUM);
    void next();
    void Pre();
    void TheFirst();
    void TheLast();
    void Play();
    void Stop();
    void Clear();
    bool playflag;
    int NowShow;

public Q_SLOTS:


private:
    QScatterDataProxy *proxy;
    QScatter3DSeries  *series;
    QScatterDataArray *dataArray;
    Q3DScatter *m_graph;
    QAbstract3DSeries::Mesh m_style;
};

#endif // SCATTERGRAPH_H
