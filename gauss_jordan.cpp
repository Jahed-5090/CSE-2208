#include <bits/stdc++.h>
using namespace std;

int n;

int GaussJordanElimination(vector<vector<double>> &AugMat, vector<double> &X)
{
     for (int j = 0; j < n; j++)
     {

          double pivot = AugMat[j][j];

          for (int k = 0; k <= n; k++)
          {
               AugMat[j][k] = AugMat[j][k] / pivot;
          }

          for (int i = 0; i < n; i++)
          {
               if (i == j)
                    continue; // skip the pivot row itself

               double ratio = AugMat[i][j] / AugMat[j][j]; // AugMat[j][j] is 1 now, but kept for clarity
               for (int k = 0; k <= n; k++)
               {
                    AugMat[i][k] = AugMat[i][k] - AugMat[j][k] * ratio;
               }
          }
     }

     int rank_A = 0;
     int rank_AB = 0;

     for (int i = 0; i < n; i++)
     {
          bool non_zero_A = false;
          bool non_zero_AB = false;

          // Check the coefficient part (left n columns) for Rank(A)
          for (int j = 0; j < n; j++)
          {
               if (abs(AugMat[i][j]) > 1e-9)
               {
                    non_zero_A = true;
                    non_zero_AB = true; // If A is non-zero, A|B is automatically non-zero
                    break;
               }
          }

          if (abs(AugMat[i][n]) > 1e-9)
          {
               non_zero_AB = true;
          }

          if (non_zero_A)
               rank_A++;
          if (non_zero_AB)
               rank_AB++;
     }

     if (rank_A < rank_AB)
     {
          return -1; // No Solution
     }
     else if (rank_A == rank_AB && rank_A < n)
     {
          return 0; // Infinite Solutions
     }
     else // rank_A == rank_AB == n
     {
          for (int i = 0; i < n; i++)
          {
               X[i] = AugMat[i][n];
          }
          return 1; // Unique Solution
     }
}

void printRREF(vector<vector<double>> &AugMat)
{
     cout << "\nReduced Row Echelon Form:\n";
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j <= n; j++)
          {
               if (abs(AugMat[i][j]) < 1e-9)
                    AugMat[i][j] = 0.0;
               cout << fixed << setprecision(3) << setw(10) << AugMat[i][j];
          }
          cout << endl;
     }
}

int main()
{
     cout << "Enter number of equations: ";
     cin >> n;

     vector<vector<double>> AugMat(n, vector<double>(n + 1));

     cout << "Enter the augmented matrix:\n";
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j < n + 1; j++)
          {
               cin >> AugMat[i][j];
          }
     }

     vector<double> X(n, 0.0);
     int status = GaussJordanElimination(AugMat, X);

     printRREF(AugMat);

     if (status == -1)
     {
          cout << "\nRank(A) < Rank(A|B)\n";
          cout << "The system is INCONSISTENT. (No Solution)\n";
     }
     else if (status == 0)
     {
          cout << "\nRank(A) == Rank(A|B) < Number of Variables\n";
          cout << "The system is DEPENDENT. (Infinite Solutions)\n";
     }
     else
     {
          

          cout << "\nRank(A) == Rank(A|B) == Number of Variables (" << n << ")\n";
          cout << "Solution:\n";
          for (int i = 0; i < n; i++)
          {
               cout << "x" << i + 1 << " = " << fixed << setprecision(3) << X[i] << endl;
          }
     }

     return 0;
}

/*
Unique solution:
n=3
2 1 1 10
3 2 3 18
1 4 9 16 
No Solution:
3
1 1 1 3
1 -1 1 1
2 0 2 10 
Infinite solution:
3
1 1 1 3
1 -1 1 1
2 0 2 4
*/
