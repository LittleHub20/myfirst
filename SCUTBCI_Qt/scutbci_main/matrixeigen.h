#ifndef MATRIXEIGEN_H
#define MATRIXEIGEN_H

#include <Eigen/Dense>

using namespace Eigen;

class MatrixEigen
{
public:
    static double var(VectorXd a)
    {
        double m = a.mean();
        VectorXd ap = (a.array() - m).matrix();
        return ap.dot(ap)/(a.size()-1);
    }

    static double stddev(VectorXd a)
    {
        return std::sqrt(var(a));
    }

    static double cov(VectorXd a, VectorXd b)
    {
        double ma = a.mean();
        double mb = b.mean();
        VectorXd ap = (a.array() - ma).matrix();
        VectorXd bp = (b.array() - mb).matrix();
        double out = ap.dot(bp)/(a.size() - 1);
        return out;
    }

    static MatrixXd zscore(MatrixXd a)
    {
        MatrixXd b(a.rows(), a.cols());
        for (int i=0; i<a.cols(); i++)
        {
            double ma = a.col(i).mean();
            double stda = stddev(a.col(i));
            b.col(i) = ((a.col(i).array()-ma)/stda).matrix();;
        }
        return b;
    }

    static MatrixXd scale(MatrixXd a)
    {
        MatrixXd b(a.rows(), a.cols());
        for (int i=0; i<a.cols(); i++)
        {
            double maxv = a.col(i).maxCoeff();
            double minv = a.col(i).minCoeff();
            b.col(i) = ((a.col(i).array()-minv)/(maxv-minv)).matrix();;
        }
        return b;
    }

    static MatrixXd downsample(MatrixXd a, int dfs)
    {
        // int offset = dfs/2;
        int newlen = a.rows()/dfs;
        MatrixXd b(newlen, a.cols());
        for (int i=0; i<a.cols(); i++)
        {
            for (int j=0; j<newlen; j++)
            {
                b(j,i) = a.col(i).segment(j*dfs, dfs).mean(); // +offset
            }
        }
        return b;
    }

    static VectorXd sort(VectorXd& a, bool ascend = true)
    {
        VectorXd indices(a.size());
        for (int i=0; i<a.size(); i++)
            indices[i] = i;

        int temp1;
        double temp2;
        for (int i=0; i<a.size()-1; i++)
        {
            for (int j = i+1; j<a.size(); j++)
            {
                if (ascend) {
                    if (a[i] > a[j]) {
                        temp1 = indices[i]; indices[i] = indices[j]; indices[j] = temp1;
                        temp2 = a[i]; a[i] = a[j]; a[j] = temp2;
                    }
                } else {
                    if (a[i] < a[j]) {
                        temp1 = indices[i]; indices[i] = indices[j]; indices[j] = temp1;
                        temp2 = a[i]; a[i] = a[j]; a[j] = temp2;
                    }
                }
            }
        }
        return indices;
    }

    /*
     * Compute the eigenvalues of X'*X by SVD
     * X is a N by P design matrix
    */
    static VectorXd myeig(MatrixXd X)
    {
        int N = X.rows();
        int P = X.cols();
        int M = N<P ? N : P;
        BDCSVD<MatrixXd> svd(X);
        VectorXd S = svd.singularValues();
        VectorXd d1 = S.array()*S.array();
        VectorXd d = VectorXd::Zero(P);
        d.segment(0, M) = d1.segment(0, M);
        return d;
    }

    /*
     * Calculate the Woodbury identity
     * (A + BD^{-1}C)^{-1} = A^{-1} - A^{-1}B(D+CA^{-1}B)^{-1}CA^{-1}
     * which is useful when A is large and diagonal, and hence easy to invert,
     * while B has many rows but few columns (and conversely for C) so that
     * the right-hand side is much cheaper to evaluate than the left-hand side.
     * We consider this condition only.
    */
    static MatrixXd inverseWoodbury(MatrixXd A, MatrixXd B, MatrixXd C, MatrixXd D)
    {
        VectorXd vecA = A.diagonal();
        MatrixXd invA = vecA.cwiseInverse().asDiagonal();
        MatrixXd invAB = invA*B;
        // WD = invA - invA*B*(D+C*invA*B)^(-1)*C*invA;
        MatrixXd WD = invA - invAB*(D+C*invAB).inverse()*C*invA;
        return WD;
    }
};

#endif // MATRIXEIGEN_H
