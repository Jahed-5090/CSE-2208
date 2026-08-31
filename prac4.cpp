#include <bits/stdc++.h>
using namespace std;

double a4, a3, a2, a1, a0;
double E = 1e-4;

double f(double x)
{
     return a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * pow(x, 1) + a0;
}

double falsePosition(double x1, double x2, int &itr)
{

     itr = 0;
     double x0 = x1;

     while (fabs(f(x1) - f(x2)) >= E)
     {
          itr++;
          x0 = x1 - f(x1) * ((x2 - x1) / (f(x2) - f(x1)));

          if (f(x0) == 0.0)
               break;
          else if (f(x1) * f(x0) < 0.0)
          {
               x2 = x0;
          }
          else if (f(x2) * f(x0) < 0.0)
          {
               x1 = x0;
          }
     }

     return x0;
}

int main()
{

     cout << "\nEnter the coefficients a4 a3 a2 a1 a0 : ";
     cin >> a4 >> a3 >> a2 >> a1 >> a0;
     cout << endl;

     double xmax = sqrt(pow(a3 / a4, 2) - 2 * (a2 / a4));

     double lo = -fabs(xmax);
     double hi = xmax;

     double a = lo;

     int rootCount = 0;

     int itr;
     double step_size = 0.5;

     while (a < hi)
     {

          double b = a + step_size;

          if (f(a) * f(b) < 0.0)
          {
               rootCount++;
               double root = falsePosition(a, b, itr);
               cout << rootCount << "th root is : " << root << endl;
               cout << "Searching Interval is : [" << a << " " << b << "]" << endl;
               cout << "totoal iteration is : " << itr << endl
                    << endl;
          }

          a = b;
     }

     if (rootCount == 0)
     {
          cout << "real root not available\n";
     }

     return 0;
}