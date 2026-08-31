#include <bits/stdc++.h>
using namespace std;

/*
 * SECANT METHOD  (from "Secant Method (Cont.)" slide, Table 2)
 * -----------------------------------------------------------------------
 * Secant is an OPEN method: it does not strictly require f(x0)*f(x1) < 0,
 * only two initial guesses x0, x1. The slide's own worked example used
 * x0 = 0, x1 = 1 -- which happen to satisfy f(x0)*f(x1) < 0 -- so, to stay
 * consistent with Bisection/False Position/Newton-Raphson in this lab, we
 * still auto-search [-100, 100] for such a pair and use them as x0, x1.
 *
 * Step 1: Choose 2 initial guesses x0 and x1, and stopping criterion E.
 * Step 2: Find x_{n+1} = x_n - f(x_n) * (x_n - x_{n-1}) / (f(x_n) - f(x_{n-1}))
 * Step 3: If |x_{n+1} - x_n| < E, then the root is x_{n+1} -> Stop.
 *         Otherwise, set x_{n-1} = x_n, x_n = x_{n+1}, and repeat Step 2.
 */

double E = 0.0001;

// function: f(x) = 3x - cos(x) - 1
double f(double x)
{
    return 3 * x - cos(x) - 1;
}

void SECANT_METHOD(double x0, double x1)
{
    double x_prev = x0;   // x_{n-1}
    double xn     = x1;   // x_n
    double x_next;
    int itr = 0;

    cout << "Starting Secant Method with x0 = " << x0
         << ", x1 = " << x1 << "\n" << endl;

    while (true)
    {
        itr++;

        double f_prev = f(x_prev);
        double f_curr = f(xn);

        // Safety check: avoid dividing by (nearly) zero
        if (fabs(f_curr - f_prev) < 1e-12)
        {
            cout << "f(x_n) - f(x_(n-1)) is nearly zero -- Secant method fails here." << endl;
            return;
        }

        // Step 2: Secant formula
        x_next = xn - f_curr * (xn - x_prev) / (f_curr - f_prev);

        cout << "Iteration " << itr
             << " : x_(n-1) = " << x_prev
             << ", x_n = "      << xn
             << ", f(x_n) = "   << f_curr
             << ", x_(n+1) = "  << x_next << endl;

        // Step 3: stopping criterion
        if (fabs(x_next - xn) < E)
        {
            cout << "\nRoot found: x = " << x_next << endl;
            cout << "Total number of iterations = " << itr << endl;
            return;
        }

        // Otherwise shift the window forward and repeat
        x_prev = xn;
        xn     = x_next;
    }
}

int main()
{
    // Step 1: search [-100, 100] for x0, x1 such that f(x0)*f(x1) < 0
    double step_size = 0.5;
    double a = -100.0;
    double x0, x1;
    bool found = false;

    cout << "Searching interval [-100, 100] (step " << step_size
         << ") for x0, x1 with f(x0)*f(x1) < 0 ...\n" << endl;

    while (a < 100.0)
    {
        double b = a + step_size;
        if (f(a) * f(b) < 0)
        {
            x0 = a;
            x1 = b;
            found = true;
            cout << "Found x0 = " << x0 << ", x1 = " << x1
                 << "  (f(x0)*f(x1) = " << f(x0) * f(x1) << " < 0)\n" << endl;
            break;
        }
        a = b;
    }

    if (!found)
    {
        // Fallback: pick arbitrary initial guesses (Secant does not need
        // a sign change to begin, since it's an open method)
        x0 = 0.0;
        x1 = 1.0;
        cout << "No sign-changing pair found in [-100, 100]. "
             << "Defaulting to x0 = 0, x1 = 1.\n" << endl;
    }

    SECANT_METHOD(x0, x1);

    return 0;
}
