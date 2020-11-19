#include <QtMath>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDomDocument>
#include "eegalgocpp.h"
#include "matrixeigen.h"

EEGAlgoCpp::AlgoParam::AlgoParam()
{
    fs = 250;
    dfs = 5;
    epochlen = 150;

    numChars = 40;
    numChannels = 30;
    numPoints = 25;
    numFeatures = 750;
    channelSelected = 0;
    timeStart = 0;
    timeStop = 150;
    freqStart = 0.5;
    freqStop = 10;
    coefA = 0;
    coefB = 0;

    lmin = 2;
    lmax = 6;
    nta = 0.2;

    model = 0;
}

bool EEGAlgoCpp::AlgoParam::load(QString filepath)
{
    modeldir = QFileInfo(filepath).absolutePath();
    parseXML(filepath);
    numPoints = (int)qCeil((double)(timeStop-timeStart)/dfs);
    numFeatures = numChannels*numPoints;
    return true;
}

bool EEGAlgoCpp::AlgoParam::parseXML(QString filepath)
{
    QFile file(filepath);
    // qDebug(QDir::currentPath().toLocal8Bit());
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug(QString("Open file [%1] failed").arg(filepath).toLocal8Bit());
        return false;
    }

    QString error;
    int row = 0, column = 0;
    QDomDocument document;
    if(!document.setContent(&file, false, &error, &row, &column)) {
        qDebug(QString("Parse file failed at line row %1 and column %2")
               .arg(row).arg(column).toLocal8Bit());
        return false;
    }

    if(document.isNull()) {
        qDebug("Document is null!");
        return false;
    }

    QStringList strList;
    QDomElement root, item;
    root = document.documentElement();
    item = root.firstChildElement("fs"); fs = item.text().toInt();
    item = root.firstChildElement("dfs"); dfs = item.text().toInt();
    item = root.firstChildElement("numChars"); numChars = item.text().toInt();
    item = root.firstChildElement("numChannels"); numChannels = item.text().toInt();
    item = root.firstChildElement("channelSelected"); strList = item.text().split(" ");
    channelSelected = new int[strList.size()];
    for (int i=0; i<strList.size(); i++)
        channelSelected[i] = strList.at(i).toInt();
    item = root.firstChildElement("timeStart"); timeStart = item.text().toInt();
    item = root.firstChildElement("timeStop"); timeStop = item.text().toInt();
    item = root.firstChildElement("freqStart"); freqStart = item.text().toDouble();
    item = root.firstChildElement("freqStop"); freqStop = item.text().toDouble();
    item = root.firstChildElement("coefA"); strList = item.text().split(" ");
    coefA = new double[strList.size()];
    for (int i=0; i<strList.size(); i++)
        coefA[i] = strList.at(i).toDouble();
    item = root.firstChildElement("coefB"); strList = item.text().split(" ");
    coefB = new double[strList.size()];
    for (int i=0; i<strList.size(); i++)
        coefB[i] = strList.at(i).toDouble();
    // filter = new SignalProcess.Filter(coefA, coefB);

    item = root.firstChildElement("classifier"); classifier = item.text();
    item = root.firstChildElement("modelfile"); modelfile = item.text();
    if (!classifier.compare("svm", Qt::CaseInsensitive)) {
        // model = new SVM();
    } else {
        model = new LinearClassifier();
    }
    QString strModelPath = modeldir+"/"+modelfile;
    model->load(strModelPath);

    return true;
}

EEGAlgoCpp::AlgoState::AlgoState()
{
    numChars = 40;
    numFeatures = 750;
    charRepeated = 0;
    featureAccumulated = 0;
    charIndex = 0;
    roundIndex = 0;
    trialIndex = 0;
    maxRound = 10;
    kr = 0;
}

void EEGAlgoCpp::AlgoState::init(int charaters, int features, int maxround)
{
    numChars = charaters;
    numFeatures = features;
    maxRound = maxround;
    charRepeated = new int[charaters];
    reset();

    while (featureRounds.size() > 0) {
        double* temp = featureRounds.takeFirst();
        delete temp;
    }
    fscoreDelta.clear();
    roundUse.clear();
}

void EEGAlgoCpp::AlgoState::reset()
{
    if (charRepeated)
        memset(charRepeated, 0, sizeof(int)*numChars);
    featureAccumulated = new double[numChars*numFeatures];
    memset(featureAccumulated, 0, sizeof(double)*(numChars*numFeatures));
}

void EEGAlgoCpp::init()
{
    qDebug("EEGAlgoCpp::init() called");
    if (m_strModelPath.size() > 0) {
        param.load(m_strModelPath);
        state.init(param.numChars, param.numFeatures, param.lmax);
        ypred = new int[param.numChars];
        yprob = new double[param.numChars];
    }
}

void EEGAlgoCpp::reset()
{
    qDebug("EEGAlgoCpp::reset() called");
    state.reset();
}

void EEGAlgoCpp::round()
{
    // qDebug("EEGAlgoCpp::round() called");
    int i;
    if((m_nEvent > 0) && (m_nEvent <= param.numChars)) {
        qDebug(QString("Process event: %1, index: %2, round: %3")
               .arg(m_nEvent).arg(state.charIndex).arg(state.kr).toLocal8Bit());
        // channel selection
        Map<MatrixXd> signalInput(m_pEpochData, m_nDataPoints, m_nChannels);
        MatrixXd signalFiltered(m_nDataPoints, param.numChannels);
        for (i=0; i<param.numChannels; i++)
        {
            signalFiltered.col(i) = signalInput.col(i);
        }
        // filtering
        // param.filter.filtfilt(signalFiltered, signalFiltered);
        // time selection
        MatrixXd signalTime(param.timeStop-param.timeStart, param.numChannels);
        for (i=0; i<param.numChannels; i++)
        {
            signalTime.col(i) = signalFiltered.block(param.timeStart, i, param.timeStop-param.timeStart, 1);
        }
        // downsampling
        MatrixXd signalDownsampled(param.numPoints, param.numChannels);
        signalDownsampled = MatrixEigen::downsample(signalTime, param.dfs);
        // normalizing
        signalDownsampled = MatrixEigen::zscore(signalDownsampled);
        // feature extracting
        Map<VectorXd> feature(signalDownsampled.data(), param.numFeatures);
        Map<MatrixXd> featureAccumulated(state.featureAccumulated, param.numFeatures, param.numChars);
        featureAccumulated.col(m_nEvent-1) += feature;
        state.charRepeated[m_nEvent-1] ++;

        state.charIndex ++;
        if (state.charIndex >= param.numChars) {
            state.charIndex = 0;
            state.roundIndex ++;
            evaluate();
        }
    }
}

void EEGAlgoCpp::evaluate()
{
    qDebug("EEGAlgoCpp::evaluate() called");
    int i;
    state.kr ++;
    state.featureRounds.append(state.featureAccumulated);
    if (state.featureRounds.size() > param.lmax) {
        double* featureOld = state.featureRounds.takeFirst();
        delete featureOld;
    }

    if (state.kr >= param.lmin) {
        if (state.kr > param.lmax) {
            state.kr = param.lmax;
        }

        MatrixXd featureAveraged = MatrixXd::Zero(param.numFeatures, param.numChars);
        for (i = 0; i < state.kr; i++) {
            Map<MatrixXd> featureRound(state.featureRounds.at(state.featureRounds.size()-i-1),
                                       param.numFeatures, param.numChars);
            featureAveraged += featureRound;
        }

        for (i = 0; i < param.numChars; i++) {
            if (state.charRepeated[i] > 0) {
                featureAveraged.col(i) /= featureAveraged.col(i).norm();
            } else {
                featureAveraged.col(i) = VectorXd::Zero(param.numFeatures);
            }
        }

        int index = -1;
        memset(ypred, 0, sizeof(int)*param.numChars);
        memset(yprob, 0, sizeof(double)*param.numChars);
        param.model->predict(featureAveraged.data(), ypred, yprob,
                             param.numChars, param.numFeatures);
        Map<VectorXd> fscore_raw(yprob, param.numChars);
        fscore_raw.maxCoeff(&index);
        VectorXd fscore_normalized(param.numChars);
        fscore_normalized = MatrixEigen::scale(fscore_raw);
        MatrixEigen::sort(fscore_normalized, false); // descending order
        double fscore_delta = fscore_normalized[0] - fscore_normalized[1];
        // state.fscoreDelta.append(fscore_delta);

        if (state.kr >= param.lmax) {
            state.trialIndex ++;
            // state.roundUse.append(state.kr);
            state.kr = 0;
            m_nResult = index;
        } else if (fscore_delta >= param.nta) {
            state.trialIndex = state.trialIndex + 1;
            // state.roundUse.append(state.kr);
            state.kr = 0;
            m_nResult = index;
        } else
            m_nResult = -1;
    } else {
        m_nResult = -1;
    }
    reset();
}
