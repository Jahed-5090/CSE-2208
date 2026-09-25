#include <bits/stdc++.h>
using namespace std;

int n;

int GaussJordan(vector<vector<double>> &AugMat, vector<double> &X)
{
    for (int j = 0; j < n; j++)
    {
        double pivot = AugMat[j][j];
        for (int k = 0; k <= n; k++)
            AugMat[j][k] /= pivot;

        for (int i = 0; i < n; i++)
        { 
            if(i==j) continue; 

            double ratio = AugMat[i][j] / AugMat[j][j];
            for (int k = 0; k <= n; k++)
            {
                AugMat[i][k] = AugMat[i][k] - ratio * AugMat[j][k];
            }
        }
    }

    int rankA = 0;
    int rankAB = 0;

    for (int i = 0; i < n; i++)
    {
        bool nonzeroA = false;
        bool nonzeroAB = false;

        for (int j = 0; j < n; j++)
        {
            if (abs(AugMat[i][j]) > 1e-9)
            {
                nonzeroA = true;
                nonzeroAB = true;
                break;
            } 
            
        }
        if(fabs(AugMat[i][n])>1e-9) nonzeroAB = true ;
            if (nonzeroA)
                rankA++;
            if (nonzeroAB)
                rankAB++;
    }

    if (rankA < rankAB)
    {
        return 0;
    }
    else if (rankA == rankAB && rankA < n)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < n; i++)
            X[i] = AugMat[i][n];
        return 1;
    }
}

void print(vector<vector<double>> &mat)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            double x = mat[i][j] ; 
            if(fabs(x)<1e-9) x = 0.0 ;
            cout << setw(3) << setprecision(3) << x  << " ";
        }
        cout << endl;
    }
}

int main()
{

    cout << "Enter n : ";
    cin >> n;

    vector<vector<double>> AugMat(n, vector<double>(n + 1));

    vector<double> X(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cin >> AugMat[i][j];
        }
    }

    int sts = GaussJordan(AugMat, X);

    print(AugMat);

    if (sts == -1)
        cout << "INFINITE SOLKUTIO" << endl;
    else if (sts == 0)
        cout << "NO SOLN\n";
    else
    {
        cout << "UNIQUE SOLLUTION\n";
        for (int i = 0; i < n; i++)
            cout << setw(3) << setprecision(3) << X[i] << " ";
        cout << endl;
    }

    return 0;
}