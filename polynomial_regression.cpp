// Least Square Regression: Polynomial Equation
// Fits y = a0 + a1*x + a2*x^2 + ... + a(degree)*x^degree
//
// Method (same idea as the slide, extended to a general degree):
//   1. Build the "normal equations" using sums of powers of x.
//   2. Solve that small system of equations with Gaussian elimination.

#include <iostream>
#include <cmath>
using namespace std;

template <int Terms>
void gaussianElimination(double (&A)[Terms][Terms + 1]) {
    for (int i = 0; i < Terms; i++) {
        // bring the row with the largest pivot to the top (avoids divide-by-small-number)
        int pivotRow = i;
        for (int k = i + 1; k < Terms; k++) {
            if (fabs(A[k][i]) > fabs(A[pivotRow][i])) pivotRow = k;
        }
        for (int j = 0; j <= Terms; j++) {
            double temp = A[i][j];
            A[i][j] = A[pivotRow][j];
            A[pivotRow][j] = temp;
        }

        // eliminate this column from every row below
        for (int k = i + 1; k < Terms; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j <= Terms; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
}

int main() {
    // Example data from the lecture slide (fit a 2nd order polynomial)
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {6, 11, 18, 27, 38};
    int n = 5;

    const int degree = 2;        // change this to fit a different order
    const int terms = degree + 1; // number of unknown coefficients (a0, a1, ...)

    // Step 1: sum of x^0, x^1, ... , x^(2*degree)
    double sumX[2 * degree + 1] = {0};
    for (int i = 0; i < n; i++) {
        double power = 1;
        for (int k = 0; k <= 2 * degree; k++) {
            sumX[k] += power;
            power *= x[i];
        }
    }

    // Step 2: sum of (x^0)*y, (x^1)*y, ... , (x^degree)*y
    double sumXY[terms] = {0};
    for (int i = 0; i < n; i++) {
        double power = 1;
        for (int k = 0; k <= degree; k++) {
            sumXY[k] += power * y[i];
            power *= x[i];
        }
    }

    cout << "Sum x    = " << sumX[1] << endl;
    cout << "Sum x^2  = " << sumX[2] << endl;
    cout << "Sum x^3  = " << sumX[3] << endl;
    cout << "Sum x^4  = " << sumX[4] << endl;
    cout << "Sum y    = " << sumXY[0] << endl;
    cout << "Sum xy   = " << sumXY[1] << endl;
    cout << "Sum x^2y = " << sumXY[2] << endl << endl;

    // Step 3: build the normal-equation matrix (augmented with the answer column)
    double A[terms][terms + 1];
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < terms; j++) {
            A[i][j] = sumX[i + j];
        }
        A[i][terms] = sumXY[i];
    }

    // Step 4: solve the system with simple Gaussian elimination
    gaussianElimination(A);

    // Step 5: back substitution to find the coefficients
    double coeff[terms];
    for (int i = terms - 1; i >= 0; i--) {
        double sum = A[i][terms];
        for (int j = i + 1; j < terms; j++) {
            sum -= A[i][j] * coeff[j];
        }
        coeff[i] = sum / A[i][i];
    }

    cout << "Fitted polynomial: y = ";
    for (int i = 0; i < terms; i++) {
        cout << coeff[i];
        if (i > 0) cout << " * x^" << i;
        if (i != terms - 1) cout << " + ";
    }
    cout << endl;

    return 0;
}
