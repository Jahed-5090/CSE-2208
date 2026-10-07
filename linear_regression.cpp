// Least Square Regression: Linear Equation (y = a + b*x)
//
// This follows the normal equations derived in the lecture slide:
//   b = (n * sum(x*y) - sum(x) * sum(y)) / (n * sum(x^2) - (sum(x))^2)
//   a = (sum(y) - b * sum(x)) / n

#include <iostream>
using namespace std;

int main() {

    double x[] = {1, 2, 3, 4, 5, 6, 7};
    double y[] = {3, 4, 4, 5, 8, 9, 10};
    int n = 7;

    // Step 1: calculate the four sums we need
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < n; i++) {
        sumX  += x[i];
        sumY  += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    // Step 2: plug the sums into the two formulas from the slide
    double b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double a = (sumY - b * sumX) / n;

    cout << "Sum x  = " << sumX  << endl;
    cout << "Sum y  = " << sumY  << endl;
    cout << "Sum xy = " << sumXY << endl;
    cout << "Sum x^2= " << sumX2 << endl << endl;

    cout << "Fitted line: y = " << a << " + " << b << " * x" << endl << endl;

    // Step 3: show how well the fitted line matches the data
    cout << "x\ty (actual)\ty (fitted)" << endl;
    for (int i = 0; i < n; i++) {
        double yFit = a + b * x[i];
        cout << x[i] << "\t" << y[i] << "\t\t" << yFit << endl;
    }

    return 0;
}
