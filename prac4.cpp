#include <bits/stdc++.h>
using namespace std;

int n;

void decompose(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U)
{

     for (int j = 0; j < n; j++)
     {
          for (int i = j; i < n; i++)
          {
               double sum = 0.0;
               for (int k = 0; k < j; k++)
               {
                    sum += (L[i][k] * U[k][j]);
               }
               L[i][j] = A[i][j] - sum;
          }

          U[j][j] = 1.0;

          if (fabs(L[j][j]) < 1e-12)
          {
               exit(1);
          }

          for (int i = j + 1; i < n; i++)
          {
               double sum = 0.0;
               for (int k = 0; k < j; k++)
               {
                    sum += (L[j][k] * U[k][i]);
               }
               U[j][i] = (A[j][i] - sum) / L[j][j];
          }
     }
}

vector<double> forwardsubs(vector<vector<double>> &L, vector<double> &B)
{

     vector<double> Z(n, 0.0);

     for (int i = 0; i < n; i++)
     {
          double sum = 0.0;
          for (int k = 0; k < i; k++)
          {
               sum += (L[i][k] * Z[k]);
          }
          Z[i] = (B[i] - sum) / L[i][i];
     }
     return Z;
}

vector<double> backwardsubs(vector<vector<double>> &U, vector<double> &Z)
{

     vector<double> X(n, 0.0);
     for (int i = n - 1; i >= 0; i--)
     {
          double sum = 0.0;
          for (int k = i + 1; k < n; k++)
          {
               sum += U[i][k] * X[k];
          }
          X[i] = (Z[i] - sum) / U[i][i];
     }
     return X;
}

void printmatrix(vector<vector<double>> &mat)
{
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j < n; j++)
          {
               cout << setw(10) << mat[i][j] << " ";
          }
          cout << endl;
     }
}

int main()
{

     while (1)
     {

          cout << "Enter n: ";
          cin >> n;

          vector<vector<double>> augmat(n, vector<double>(n+1));

          for (int i = 0; i < n; i++)
          {
               for (int j = 0; j <= n; j++)
               {
                    cin >> augmat[i][j];
               }
          }

          vector<vector<double>> A(n, vector<double>(n, 0.0));
          vector<double> B(n, 0.0);

          for (int i = 0; i < n; i++)
          {
               for (int j = 0; j < n; j++)
               {
                    A[i][j] = augmat[i][j];
               }
          }

          for (int i = 0; i < n; i++)
               B[i] = augmat[i][n];

          vector<vector<double>> L, U;

          L.assign(n,vector<double>(n,0.0)) ;
          U.assign(n,vector<double>(n,0.0)) ;

          decompose(A, L, U);

          cout << "L" << endl;
          printmatrix(L);
          cout << "U" << endl;
          printmatrix(U);

          vector<double> Z = forwardsubs(L, B);

          vector<double> X = backwardsubs(U, Z);

          cout << "Printing the solutions sequentially: " << endl;

          for (int i = 0; i < n; i++)
          {
               cout << X[i] << endl;
          }

          cout << " Another system ? y|n : ";
          char s;
          cin >> s;

          if (s == 'n')
               break;
     }

     return 0;
}


/*
1 1 1 9
2 -3 4 13
3 4 5 40

*/