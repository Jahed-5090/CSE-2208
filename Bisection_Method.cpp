/*
 * BISECTION METHOD ALGORITHM
 * Step 1: Choose 2 real numbers x1 and x2 such that f(x1) * f(x2) < 0,
 *         and define a stopping criterion E.
 * Step 2: Define the root x0 = (x1 + x2) / 2.
 * Step 3: Find f(x0).
 * Step 4: If f(x0) == 0, then the root is x0. -> Stop
 *         If f(x0) * f(x1) < 0, then x2 = x0.
 *         If f(x0) * f(x2) < 0, then x1 = x0.
 *         Return to Step 2 until finding abs((x2 - x1) / x2) < E.
 */

#include <bits/stdc++.h>
using namespace std;

// function: x^3 - 3x + 5cos(x) = 0
double E = 0.0001;

double f(double x)
{
     return pow(x, 3) - 3 * x + 5 * cos(x);
}

void BISECTION_METHOD(double x1, double x2)
{
     double error = 1.0; // Initialized greater than E to start the loop
     int itr = 0;
     double x0;

     while (error >= E) // Keep looping while error is greater than or equal to E
     {
          itr++;
          cout << "Iteration : " << itr << endl;

          x0 = (x1 + x2) / 2.0;

          if (f(x0) == 0.0)
          {
               break;
          }
          else if (f(x1) * f(x0) < 0.0)
          {
               x2 = x0;
          }
          else if (f(x2) * f(x0) < 0.0)
          {
               x1 = x0;
          }

          error = abs((x2 - x1) / x2);
          cout << "Root is : " << x0 << endl;
     }

     cout << "Total number of iteration is : " << itr << endl;
     cout << "final root is : " << x0 << endl;

     return;
}

int main()
{
     double x1 = 0.0;
     double x2 = 0.0;

     double step_size = 0.5;

     cout << "Searching for initial values in the interval [-100,100] with step_size : " << step_size << endl;

     double a = -100.0;
     bool found_initialValues = false;

     while (a < 100.0)
     {
          double d = a + step_size;

          if (f(a) * f(d) < 0)
          {
               x1 = a;
               x2 = d;
               found_initialValues = true;
               break;
          }
          a = d;
     }

     if (!found_initialValues)
     {
          cout << "Initial values are not found in the interval [-100,100]!!!\n";
     }
     else
     {
          cout << "Initial values found: x1 = " << x1 << ", x2 = " << x2 << "\n\n";
          BISECTION_METHOD(x1, x2);
     }

     return 0;
}