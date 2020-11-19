#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include "linearclassifier.h"

LinearClassifier::LinearClassifier()
{
    n = 0;
    p = 0;
    w = 0;
    b = 0;
}

void LinearClassifier::predict(double* x, int* ypred, double* yprob, int n, int p)
{
    memset(ypred, 0, sizeof(double)*n);
    memset(yprob, 0, sizeof(double)*n);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<p; j++)
        {
            yprob[i] += x[i*p+j] * w[j];
        }
        yprob[i] += b;
        ypred[i] = yprob[i] > 0.5 ? 1 : 0;
    }
}

bool LinearClassifier::load(QString modelpath)
{
    QFile file(modelpath);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug(QString("Open file [%1] failed").arg(modelpath).toLocal8Bit());
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
    item = root.firstChildElement("b"); b = item.text().toDouble();
    item = root.firstChildElement("w"); strList = item.text().split(" ");
    p = strList.size();
    w = new double[p];
    for (int i=0; i<p; i++)
        w[i] = strList.at(i).toDouble();

    return true;
}

bool LinearClassifier::save(QString modelpath)
{
    return true;
}
