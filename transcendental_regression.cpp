// Least Square Regression: Transcendental Equation
// Fits T = a + b * f(t), where f(t) = e^(t/4)   [example form from the lecture slide]
//
// The trick from the slide: a transcendental equation like this is turned
// into a straight line by treating f(t) as if it were "x". Once we see it
// that way, we reuse the exact same two formulas as linear regression.

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Example data from the lecture slide
    double t[] = {1, 2, 3, 4, 5};
    double T[] = {50, 80, 96, 120, 145};
    int n = 5;

    // Step 1: calculate f(t) = e^(t/4) for every data point
    double f[5];
    for (int i = 0; i < n; i++) {
        f[i] = exp(t[i] / 4.0);
    }

    cout << "t\tf(t)=e^(t/4)\tT" << endl;
    for (int i = 0; i < n; i++) {
        cout << t[i] << "\t" << f[i] << "\t\t" << T[i] << endl;
    }

    // Step 2: same sums as linear regression, but using f(t) in place of x
    double sumF = 0, sumT = 0, sumFT = 0, sumF2 = 0;
    for (int i = 0; i < n; i++) {
        sumF  += f[i];
        sumT  += T[i];
        sumFT += f[i] * T[i];
        sumF2 += f[i] * f[i];
    }

    // Step 3: same two formulas as the linear case, just with f(t) instead of x
    double b = (n * sumFT - sumF * sumT) / (n * sumF2 - sumF * sumF);
    double a = (sumT - b * sumF) / n;

    cout << endl << "Fitted equation: T = " << a << " + " << b << " * e^(t/4)" << endl;

    // Step 4: use the fitted equation to estimate T when t = 6
    double t_new = 6;
    double T_predicted = a + b * exp(t_new / 4.0);
    cout << "Predicted T at t = 6 is " << T_predicted << endl;

    return 0;
}
