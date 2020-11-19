#ifndef EEGALGOCPP_H
#define EEGALGOCPP_H

#include <QVector>
#include <Eigen/Dense>
#include "eegalgoeng.h"
#include "linearclassifier.h"

using namespace Eigen;

class EEGAlgoCpp : public EEGAlgoEng
{
protected:
    class AlgoParam
    {
    public:
        int fs;
        int dfs;
        int epochlen;

        int numChars;
        int numChannels;
        int numPoints;
        int numFeatures;
        int* channelSelected;
        int timeStart;
        int timeStop;
        double freqStart;
        double freqStop;
        double* coefA;
        double* coefB;

        QString classifier;
        QString modelfile;
        QString modeldir;
        LinearClassifier* model;

        int lmin;
        int lmax;
        double nta;

    public:
        AlgoParam();
        bool load(QString filepath);
        bool parseXML(QString filepath);
    };

    class AlgoState
    {
    public:
        int numChars;
        int numFeatures;
        int* charRepeated;
        double* featureAccumulated;
        QVector<double*> featureRounds;
        QVector<double> fscoreDelta;
        QVector<int> roundUse;
        int charIndex;
        int roundIndex;
        int trialIndex;
        int maxRound;
        int kr;

    public:
        AlgoState();
        void init(int charaters, int features, int maxround);
        void reset();
    };

protected:
    int* ypred;
    double* yprob;
    AlgoParam param;
    AlgoState state;

public:

protected:
    void init();
    void reset();
    void round();
    void evaluate();
};

#endif // EEGALGOCPP_H
