#include <bits/stdc++.h>
using namespace std;

/*
 * NEWTON-RAPHSON METHOD  (Algorithm 1, "Newton-Raphson Method (Cont.)" slide)
 * -----------------------------------------------------------------------
 * Step 1: Find f'(x_n)
 * Step 2: Choose 2 real numbers a and b such that f(a)*f(b) < 0, and
 *         stopping criterion E. If such a and b do not exist, randomly
 *         guess a.
 * Step 3: Assume x0 = a
 * Step 4: Find x_{n+1} = x_n - f(x_n) / f'(x_n)
 * Step 5: If |x_{n+1} - x_n| < E, then the root is x_{n+1} -> Stop.
 *         Otherwise, set x_n = x_{n+1} and repeat (go back to Step 4).
 *
 * Note: unlike Bisection/False Position, Newton-Raphson is an OPEN method,
 * so a and b are only used to obtain ONE good starting guess x0 = a.
 * b is never used again after Step 2/3 -- the rest of the iteration only
 * needs x0 and f'(x0), f'(x1), ... at each step.
 */

double E = 0.0001;

// function: f(x) = 3x - cos(x) - 1
double f(double x)
{
    return 3 * x - cos(x) - 1;
}

// Step 1: derivative, f'(x) = 3 + sin(x)
double fprime(double x)
{
    return 3 + sin(x);
}

void NEWTON_RAPHSON_METHOD(double x0)
{
    double xn = x0;      // Step 3: x0 = a
    double x_next;
    int itr = 0;

    cout << "Starting Newton-Raphson from x0 = " << xn << "\n" << endl;

    while (true)
    {
        itr++;

        double fx  = f(xn);
        double fpx = fprime(xn);

        // Safety check: f'(x) must not be zero near the root (slide's
        // "Conditions for Convergence"), otherwise the formula divides by 0.
        if (fabs(fpx) < 1e-12)
        {
            cout << "f'(x) is nearly zero -- Newton-Raphson fails here." << endl;
            return;
        }

        // Step 4: x_{n+1} = x_n - f(x_n) / f'(x_n)
        x_next = xn - fx / fpx;

        cout << "Iteration " << itr
             << " : x_n = "   << xn
             << ", f(x_n) = " << fx
             << ", f'(x_n) = "<< fpx
             << ", x_(n+1) = "<< x_next << endl;

        // Step 5: stopping criterion
        if (fabs(x_next - xn) < E)
        {
            cout << "\nRoot found: x = " << x_next << endl;
            cout << "Total number of iterations = " << itr << endl;
            return;
        }

        xn = x_next;   // Otherwise set x_n = x_{n+1} and repeat
    }
}

int main()
{
    // Step 2: search [-100, 100] for a, b such that f(a)*f(b) < 0
    double step_size = 0.5;
    double a = -100.0;
    double x0;
    bool found = false;

    cout << "Searching interval [-100, 100] (step " << step_size
         << ") for a, b with f(a)*f(b) < 0 ...\n" << endl;

    while (a < 100.0)
    {
        double b = a + step_size;
        if (f(a) * f(b) < 0)
        {
            x0 = a;   // Step 3: x0 = a
            found = true;
            cout << "Found a = " << a << ", b = " << b
                 << "  (f(a)*f(b) = " << f(a) * f(b) << " < 0)\n" << endl;
            break;
        }
        a = b;
    }

    if (!found)
    {
        // Step 2 fallback: "If such a and b do not exist, randomly guess a."
        x0 = 0.0;
        cout << "No sign-changing interval found in [-100, 100]. "
             << "Randomly guessing a = 0.\n" << endl;
    }

    NEWTON_RAPHSON_METHOD(x0);

    return 0;
}
