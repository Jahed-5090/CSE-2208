#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// f(x) = 3x - cos(x) - 1   (as given on the slide)
double f(double x) {
    return 3 * x - cos(x) - 1;
}

int main() {
    double E = 1e-4;   // stopping criterion (tolerance)
    double x1, x2, x0;
    bool found = false;

    // ---- Step 1: Search in [-100, 100] for x1, x2 such that f(x1)*f(x2) < 0 ----
    for (int i = -100; i < 100; i++) {
        double a = i;
        double b = i + 1;
        if (f(a) * f(b) < 0) {
            x1 = a;
            x2 = b;
            found = true;
            break;   // take the very first interval found
        }
    }

    if (!found) {
        cout << "No sign change found in [-100, 100]." << endl;
        return 0;
    }

    cout << fixed << setprecision(6);
    cout << "Initial interval found: x1 = " << x1 << ", x2 = " << x2 << endl;
    cout << "f(x1) = " << f(x1) << ",  f(x2) = " << f(x2) << endl;
    cout << "f(x1)*f(x2) = " << f(x1) * f(x2) << "  (< 0, valid interval)\n" << endl;

    cout << left << setw(6)  << "Iter"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(12) << "x0"
         << setw(14) << "f(x0)"
         << setw(12) << "Error" << endl;

    int iter = 0;
    double error;

    do {
        iter++;

        // ---- Step 2: Define root x0 = (x1 + x2) / 2 ----
        x0 = (x1 + x2) / 2.0;

        // ---- Step 3: Find f(x0) ----
        double fx0 = f(x0);

        // Error estimate: abs((x2 - x1) / x2)
        error = fabs((x2 - x1) / x2);

        cout << left << setw(6)  << iter
             << setw(12) << x1
             << setw(12) << x2
             << setw(12) << x0
             << setw(14) << fx0
             << setw(12) << error << endl;

        // ---- Step 4: Check stopping condition ----
        if (fx0 == 0.0) {
            cout << "\nExact root found: x0 = " << x0 << endl;
            break;
        }

        // If f(x0)*f(x1) < 0, root lies between x1 and x0 -> replace x2 with x0
        if (f(x0) * f(x1) < 0) {
            x2 = x0;
        }
        // If f(x0)*f(x2) < 0, root lies between x0 and x2 -> replace x1 with x0
        else if (f(x0) * f(x2) < 0) {
            x1 = x0;
        }

    } while (error >= E);   // Return to Step 2 until abs((x2-x1)/x2) < E

    cout << "\nApproximate root = " << x0 << endl;
    cout << "Total iterations = " << iter << endl;

    return 0;
}