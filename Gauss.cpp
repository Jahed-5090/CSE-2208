#include <bits/stdc++.h>
using namespace std;

int n;

vector<double> GaussElimination(vector<vector<double>> &AugMat)
{

     for (int j = 0; j < n; j++)
     {
          for (int i = j + 1; i < n; i++)
          {
               double ratio = AugMat[i][j] / AugMat[j][j];
               for (int k = 0; k < n+1; k++)
               {
                    AugMat[i][k] = AugMat[i][k] - AugMat[j][k] * ratio;
               }
          }
     }

     vector<double> X(n, 0.0); 

     for(int i=n-1;i>=0;i--) {
        double sum = 0.0 ; 
        for(int j=i+1;j<n;j++) {
          sum += AugMat[i][j]*X[j] ;
        }   
        X[i]=(AugMat[i][n]-sum)/AugMat[i][i] ; 
     }


  return X ;
}

int main()
{

     cout << "Enter n : ";
     cin >> n;

     vector<vector<double>> AugMat(n, vector<double>(n + 1));

     cout << "Enter the augmented matrix : \n";

     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j < n + 1; j++)
          {
               cin >> AugMat[i][j];
          }
     }

     vector<double> X = GaussElimination(AugMat);

     cout << "Printing the solution Vector: ";
     for (auto x : X)
          cout << setw(10) << setprecision(5) << x << " ";
     cout << endl;

     return 0;
}



/*
n=3 
2 1 1 10 
3 2 3 18
1 4 9 16
*/