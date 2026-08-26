#include <bits/stdc++.h>
using namespace std;

const double E = 1e-4;
double coff[5];

double f(double x)
{
     double res = coff[4] * pow(x, 4) + coff[3] * pow(x, 3) + coff[2] * pow(x, 2) + coff[1] * pow(x, 1) + coff[0];
     return res;
}

double BISECTION_METHOD(double x1, double x2, int &itr)
{

     double x0 = (x1 + x2) / 2.0;

     while (fabs(f(x1) - f(x2)) >= E)
     {

          x0 = (x1 + x2) / 2;
          double fx0 = f(x0);
          double fx1 = f(x1);
          double fx2 = f(x2);

          if (fx0 == 0.0)
          {
               break;
          }
          else if (fx1 * fx0 < 0.0)
          {
               x2 = x0;
          }
          else if (fx2 * fx0 < 0.0)
          {
               x1 = x0;
          }
          itr++;
     }

     return (x1 + x2) / 2.0;
}

int main()
{

     cout << "\nEnter the coefficients of a4 a3 a2 a1 a0 : ";

     for (int i = 4; i >= 0; i--)
          cin >> coff[i];

     double a4, a3, a2, a1, a0;

     a4 = coff[4];
     a3 = coff[3];
     a2 = coff[2];
     a1 = coff[1];
     a0 = coff[0];

     double xmax = sqrt(pow((a3 / a4), 2) - 2 * (a2 / a4));

     double lo = -fabs(xmax);
     double hi = fabs(xmax);
     double step_size = 0.5;

     cout << "Search Intervals are : [" << lo << " " << hi << "]" << endl;
     cout << "|XMAX| : " << xmax << endl << endl << endl ;

     int rootCount = 0;

     double a = lo;

     while (a < hi)
     {

          double b = a + step_size;

          if (f(a) * f(b) < 0.0)
          {
               rootCount++;
               int itr = 0;
               double root = BISECTION_METHOD(a, b, itr);

               string label = to_string(rootCount) + "th";

               cout << label << " root is : " << root << endl;
               cout << "Search Intervals for root is : [" << a << " " << b << "]" << endl;
               cout << "Total Number of iterations  : " << itr << endl << endl ; 
          }
          a = b;
     }

     if (rootCount == 0)
     {
          cout << "Real roots are not available in the given interval!\n";
     }

     return 0;
}