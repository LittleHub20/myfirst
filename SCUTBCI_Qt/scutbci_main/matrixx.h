#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

class MatrixX
{
public:
    static void clone(double* a, double* out, int n)
    {
        memcpy(out, a, sizeof(double)*n);
    }

    static void clone(double* a, double* out, int n, int m)
    {
        memcpy(out, a, sizeof(double)*m*n);
    }

    static void plus(double* a, double b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i] + b;
        }
    }

    static void plus(double* a, double* b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i] + b[i];
        }
    }

    static void plus(double* a, double b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j] + b;
            }
        }
    }

    static void plus(double* a, double* b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j] + b[i*m+j];
            }
        }
    }

    static void minus(double* a, double b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i] - b;
        }
    }

    static void minus(double* a, double* b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i] - b[i];
        }
    }

    static void minus(double* a, double b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j] - b;
            }
        }
    }

    static void minus(double* a, double* b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j] - b[i*m+j];
            }
        }
    }

    static double dotprod(double* a, double* b, int n)
    {
        double out = 0;
        for (int i=0; i<n; i++)
        {
            out += a[i]*b[i];
        }
        return out;
    }

    static double dotprod(double* a, double* b, int n, int m)
    {
        double out = 0;
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m;j++){
                out += a[i*m+j]*b[i*m+j];
            }
        }
        return out;
    }

    static void product(double* a, double b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i] * b;
        }
    }

    static void product(double* a, double b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j] * b;
            }
        }
    }

    /**
        * @param a a[n][m]
        * @param b b[m]
        * @param out return out[n]
        */
    static void product(double* a, double* b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = dotprod(&a[i*m], b, m);
        }
    }

    /**
        * @param a a[n][l]
        * @param b b[m][l]
        * @param out return out[n][m]
        */
    static void product(double* a, double* b, double* out, int n, int m, int l)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = dotprod(&a[i*l], &b[j*l], l);
            }
        }
    }

    static void divide(double* a, double b, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = a[i]/b;
        }
    }

    static void divide(double* a, double b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                out[i*m+j] = a[i*m+j]/b;
            }
        }
    }

    static void zeros(int* a, int n)
    {
        for (int i=0; i<n; i++)
        {
            a[i] = 0;
        }
    }

    static void zeros(int* a, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
               a[i*m+j] = 0;
            }
        }
    }

    static void zeros(double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = 0;
        }
    }

    static void zeros(double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
               out[i*m+j] = 0;
            }
        }
    }

    /**
        * @param out return out[n][n]
        */
    static void eye(double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            for (int j = 0; j<n; j++)
            {
                out[i*n+j] = 0;
            }
            out[i*(n+1)] = 1;
        }
    }

    static void transpose(double* a, int n, int m)
    {
        double* tmp = new double[n*m];
        memcpy(tmp, a, sizeof(double)*m*n);
        transpose(tmp, a, n, m);
    }

    static void transpose(double* a, double* b, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                b[j*n+i] = a[i*m+j];
            }
        }
    }

    static double norm2(double* a, int n)
    {
        double out = 0;
        for (int i=0; i<n; i++)
        {
            out += a[i]*a[i];
        }
        out = std::sqrt(out);
        return out;
    }

    static double normfro(double* a, int n, int m)
    {
        double out = 0;
        for (int i=0; i<n; i++)
        {
            for (int j =0; j<m; j++)
            {
                out += a[i*m+j]*a[i*m+j];
            }
        }
        out = std::sqrt(out);
        return out;
    }

    static int compare(int *a, int *b, int n)
    {
        for (int i=0; i<n; i++)
        {
            if (a[i] != b[i]){
                return 0;
            }
        }
        return 1;
    }

    static int compare(int *a, int *b, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (a[i*m+j] != b[i*m+j]){
                    return 0;
                }
            }
        }
        return 1;
    }

    static int compare(double* a, double* b, int n)
    {
        double* c = new double[n];
        minus(a, b, c, n);
        double res = norm2(c, n);
        for (int i=0; i<n; i++)
        {
            if (res > 0.000001){
                return 0;
            }
        }
        delete [] c;
        return 1;
    }

    static int compare(double* a, double* b, int n, int m)
    {
        double* c = new double[n*m];
        minus(a, b, c, n, m);
        double res = normfro(c, n, m);
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++)
            {
                if (res > 0.000001){
                    return 0;
                }
            }
        }
        delete [] c;
        return 1;
    }

    static void abs(double* a, double* out, int n)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = std::abs(a[i]);
        }
    }

    static void abs(double* a, double* out, int n, int m)
    {
        for (int i=0; i<m; i++)
        {
            abs(&a[i*n], &out[i*n], n);
        }
    }

    static double max(double* a, int n, int* pi = 0)
    {
        double out = a[0];
        for (int i=1; i<n; i++)
        {
            if (out < a[i]) {
                out = a[i];
                if (pi) *pi = i;
            }
        }
        return out;
    }

    static double min(double* a, int n, int* pi = 0)
    {
        double out = a[0];
        for (int i=1; i<n; i++)
        {
            if (out > a[i]) {
                out = a[i];
                if (pi) *pi = i;
            }
        }
        return out;
    }

    static double mean(double* a, int n)
    {
        double out = 0;
        for (int i=0; i<n; i++)
        {
            out += a[i];
        }
        return out/n;
    }

    static void mean(double* a, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            out[i] = mean(&a[i*m], m);
        }
    }

    static double stddev(double* a, int n)
    {
        double out = 0;
        double ma = mean(a, n);
        for (int i=0; i<n; i++)
        {
            out += (a[i]-ma)*(a[i]-ma);
        }
        return std::sqrt(out/(n-1));
    }

    static double cov(double* a, double* b, int n)
    {
        double out = 0;
        double ma = mean(a, n);
        double mb = mean(b, n);
        for (int i=0; i<n; i++)
        {
            out += (a[i]-ma)*(b[i]-mb);
        }
        return (out/(n - 1));
    }

    static void cov(double* a, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                out[i*n+j] += cov(&a[i*m],&a[j*m],m);
            }
        }
    }

    static void cov(double* a, double* b, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                out[i*n+j] += cov(&a[i*m],&b[j*m],m);
            }
        }
    }

    static void zscore(double* a, double* out, int n)
    {
        double ma = mean(a, n);
        double stda = stddev(a, n);
        for (int i=0; i<n; i++)
        {
            out[i] = (a[i]-ma)/stda;
        }
    }

    static void zscore(double* a, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            zscore(&a[i*m], &out[i*m], m);
        }
    }

    static void scale(double* a, double* out, int n)
    {
        double maxv = max(a, n);
        double minv = min(a, n);
        for (int i=0; i<n; i++)
        {
            out[i] = (a[i]-minv)/(maxv-minv);
        }
    }

    static void scale(double* a, double* out, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            scale(&a[i*m], &out[i*m], m);
        }
    }

    static void downsample(double* input, double* output, int n, int dfs)
    {
        // int offset = dfs/2;
        int newlen = n/dfs;
        for (int i=0; i<newlen; i++)
        {
            output[i] = mean(&input[i*dfs], dfs); // +offset
        }
    }

    static void downsample(double* input, double* output, int n, int m, int dfs)
    {
        int newlen = m/dfs;
        for (int i=0; i<n; i++)
        {
            downsample(&input[i*m], &output[i*newlen], m, dfs);
        }
    }

    static void print(int* a, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m-1; j++)
            {
                printf("%d, ", a[i*m+j]);
            }
            printf("%d\n", a[i*m+m-1]);
        }
    }

    static void print(int* a, int n)
    {
        for (int i=0; i<n-1; i++)
        {
            printf("%d, ", a[i]);
        }
        printf("%d\n", a[n-1]);
    }

    static void print(double* a, int n, int m)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m-1; j++)
            {
                printf("%.4f, ", a[i*m+j]);
            }
            printf("%.4f\n", a[i*m+m-1]);
        }
    }

    static void print(double* a, int n)
    {
        for (int i=0; i<n-1; i++)
        {
            printf("%.4f, ", a[i]);
        }
        printf("%.4f\n", a[n-1]);
    }

    static void sort(double* a, double* index, int n, bool ascend)
    {
        for (int i=0; i<n; i++)
            index[i] = i;

        int temp1;
        double temp2;
        for (int i=0; i<n-1; i++)
        {
            for (int j = i+1; j<n; j++)
            {
                if (ascend) {
                    if (a[i] > a[j]) {
                        temp1 = index[i]; index[i] = index[j]; index[j] = temp1;
                        temp2 = a[i]; a[i] = a[j]; a[j] = temp2;
                    }
                } else {
                    if (a[i] < a[j]) {
                        temp1 = index[i]; index[i] = index[j]; index[j] = temp1;
                        temp2 = a[i]; a[i] = a[j]; a[j] = temp2;
                    }
                }
            }
        }
    }
};

#endif // MATRIX_H
