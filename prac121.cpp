#include <bits/stdc++.h>
using namespace std;

int n;

int GuassJordan(vector<vector<double>> &AugMat, vector<double> &X)
{

     for (int j = 0; j < n; j++)
     {

          double pivot = AugMat[j][j];

          for (int k = 0; k <= n; k++)
               AugMat[j][k] /= pivot;

          for (int i = 0; i < n; i++)
          {
               if (i == j)
                    continue;

               double ratio = AugMat[i][j] / AugMat[j][j];

               for (int k = 0; k <= n; k++)
               {
                    AugMat[i][k] = AugMat[i][k] - (ratio * AugMat[j][k]);
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
               if (AugMat[i][j] > 1e-9)
               {
                    nonzeroA = true;
                    nonzeroAB = true;
                    break;
               }
          }
          if (AugMat[i][n] > 1e-9)
          {
               nonzeroAB = true;
          }

          if (nonzeroA)
          {
               rankA++;
          }
          if (nonzeroAB)
               rankAB++;
     }

     if (rankA < rankAB)
     {
          return -1;
     }
     else if (rankA == rankAB && rankA < n)
     {
          return 0;
     }
     else
     {
          for (int i = 0; i < n; i++)
          {
               X[i] = AugMat[i][n];
          }
          return 1;
     }
}

int main()
{

     return 0;
}