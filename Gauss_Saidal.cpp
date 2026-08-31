/*
 * GAUSS-SEIDEL METHOD ALGORITHM
 * Same as Jacobi, EXCEPT: as soon as a new x_i is computed within
 * a sweep, use it immediately for computing the remaining x_i in
 * that SAME sweep (instead of waiting for the next iteration).
 * This is the only structural difference from Jacobi.
 */

#include <bits/stdc++.h>
using namespace std;

const double E = 1e-4;
int n;
double a[10][10];
double b[10];

void GAUSS_SEIDEL_METHOD()
{
    double x[10] = {0}; // initial guess
    int itr = 0;
    double error = 1.0;

    while (error >= E)
    {
        itr++;
        error = 0.0;

        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    sum += a[i][j] * x[j]; // uses UPDATED x[j] if j < i already done this sweep
            }
            double x_new_i = (b[i] - sum) / a[i][i];

            error = max(error, fabs(x_new_i - x[i]));
            x[i] = x_new_i; // update in place, immediately usable
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

    GAUSS_SEIDEL_METHOD();

    return 0;
}