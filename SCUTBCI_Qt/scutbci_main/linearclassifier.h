#ifndef LINEARCLASSIFIER_H
#define LINEARCLASSIFIER_H

#include <Eigen/Dense>

class LinearClassifier
{
protected:
    int n;
    int p;
    double* w;
    double b;

public:
    LinearClassifier();
    void predict(double* x, int* ypred, double* yprob, int n, int p);
    bool load(QString modelpath);
    bool save(QString modelpath);
};

#endif // LINEARCLASSIFIER_H
