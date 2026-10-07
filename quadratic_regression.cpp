// Least Square Regression: 2nd Order Polynomial (y = a0 + a1*x + a2*x^2)
//
// For a quadratic fit, the three normal equations are:
//   sum(y)     = n*a0    + a1*sum(x)   + a2*sum(x^2)
//   sum(xy)    = a0*sum(x)  + a1*sum(x^2) + a2*sum(x^3)
//   sum(x^2*y) = a0*sum(x^2) + a1*sum(x^3) + a2*sum(x^4)
//
// This program solves these three equations directly (by elimination),
// one step at a time, instead of using a general matrix solver.

#include <iostream>
using namespace std;

int main() {
    // Example data from the lecture slide
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {6, 11, 18, 27, 38};
    int n = 5;

    // Step 1: calculate all the sums needed for the three normal equations
    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0;
    double sumY = 0, sumXY = 0, sumX2Y = 0;

    for (int i = 0; i < n; i++) {
        double xi = x[i];
        double yi = y[i];

        sumX   += xi;
        sumX2  += xi * xi;
        sumX3  += xi * xi * xi;
        sumX4  += xi * xi * xi * xi;

        sumY   += yi;
        sumXY  += xi * yi;
        sumX2Y += xi * xi * yi;
    }

    cout << "Sum x    = " << sumX   << endl;
    cout << "Sum x^2  = " << sumX2  << endl;
    cout << "Sum x^3  = " << sumX3  << endl;
    cout << "Sum x^4  = " << sumX4  << endl;
    cout << "Sum y    = " << sumY   << endl;
    cout << "Sum xy   = " << sumXY  << endl;
    cout << "Sum x^2y = " << sumX2Y << endl << endl;

    // Step 2: write the three normal equations as
    //   n*a0    + sumX*a1  + sumX2*a2 = sumY     ... (1)
    //   sumX*a0 + sumX2*a1 + sumX3*a2 = sumXY    ... (2)
    //   sumX2*a0+ sumX3*a1 + sumX4*a2 = sumX2Y   ... (3)

    // Step 3: eliminate a0 from equations (2) and (3) using equation (1)
    // (2) - (sumX/n)*(1)  -->  removes a0 from (2)
    double factor2 = sumX / n;
    double c1_2 = sumX2 - factor2 * sumX;   // new coefficient of a1
    double c2_2 = sumX3 - factor2 * sumX2;  // new coefficient of a2
    double rhs_2 = sumXY - factor2 * sumY;  // new right-hand side

    // (3) - (sumX2/n)*(1)  -->  removes a0 from (3)
    double factor3 = sumX2 / n;
    double c1_3 = sumX3 - factor3 * sumX;
    double c2_3 = sumX4 - factor3 * sumX2;
    double rhs_3 = sumX2Y - factor3 * sumY;

    // Step 4: eliminate a1 from the new equation (3) using the new equation (2)
    double factor = c1_3 / c1_2;
    double c2_final = c2_3 - factor * c2_2;
    double rhs_final = rhs_3 - factor * rhs_2;

    // Step 5: back substitution to find a2, then a1, then a0
    double a2 = rhs_final / c2_final;
    double a1 = (rhs_2 - c2_2 * a2) / c1_2;
    double a0 = (sumY - sumX * a1 - sumX2 * a2) / n;

    cout << "Fitted polynomial: y = " << a0 << " + " << a1 << " * x + " << a2 << " * x^2" << endl << endl;

    // Step 6: show how well the fitted curve matches the data
    cout << "x\ty (actual)\ty (fitted)" << endl;
    for (int i = 0; i < n; i++) {
        double yFit = a0 + a1 * x[i] + a2 * x[i] * x[i];
        cout << x[i] << "\t" << y[i] << "\t\t" << yFit << endl;
    }

    return 0;
}
