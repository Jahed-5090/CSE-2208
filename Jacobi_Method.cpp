/*
 * JACOBI METHOD ALGORITHM
 * Step 1: Rearrange each equation i to solve for x_i:
 *         x_i = (b_i - sum(a_ij * x_j, for j != i)) / a_ii
 * Step 2: Using ALL values from the PREVIOUS iteration, compute
 *         every new x_i simultaneously (don't use updated values mid-sweep).
 * Step 3: Find the max absolute difference between new and old x values.
 * Step 4: Repeat until max difference < E.
 */

#include <bits/stdc++.h>
using namespace std;

const double E = 1e-4;
int n;
double a[10][10]; // coefficient matrix
double b[10];     // right-hand side

void JACOBI_METHOD()
{
     double x[10] = {0}; // initial guess
     double x_new[10] = {0};
     int itr = 0;
     double error = 1.0;

     while (error >= E)
     {
          itr++;

          for (int i = 0; i < n; i++)
          {
               double sum = 0.0;
               for (int j = 0; j < n; j++)
               {
                    if (j != i)
                         sum += a[i][j] * x[j]; // uses OLD values only
               }
               x_new[i] = (b[i] - sum) / a[i][i];
          }

          error = 0.0;
          for (int i = 0; i < n; i++)
          {
               error = max(error, fabs(x_new[i] - x[i]));
               x[i] = x_new[i]; // update for next iteration
          }

          cout << "Iteration : " << itr << "  ->  ";
          for (int i = 0; i < n; i++)
               cout << "x" << i + 1 << " = " << x[i] << "  ";
          cout << endl;
     }

     cout << "\nTotal number of iterations : " << itr << endl;
     cout << "Final solution : ";
     for (int i = 0; i < n; i++)
          cout << "x" << i + 1 << " = " << x[i] << "  ";
     cout << endl;
}

int main()
{
     cout << "Enter number of equations (n) : ";
     cin >> n;

     cout << "Enter the coefficient matrix (a[i][j]) and RHS (b[i]) row by row:\n";
     for (int i = 0; i < n; i++)
     {
          for (int j = 0; j < n; j++)
               cin >> a[i][j];
          cin >> b[i];
     }

     JACOBI_METHOD();

     return 0;
}