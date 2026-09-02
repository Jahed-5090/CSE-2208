#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Evaluates the polynomial f(x) = a_n*x^n + a_{n-1}*x^{n-1} + ... + a_1*x + a_0
double f(double x, const vector<double> &coeffs)
{
     double result = 0.0;
     int n = coeffs.size() - 1;
     for (int i = 0; i <= n; i++)
     {
          result += coeffs[i] * pow(x, n - i);
     }
     return result;
}

// Helper function to print the polynomial in the requested format
void print_polynomial(const vector<double> &coeffs)
{
     int n = coeffs.size() - 1;
     bool first = true;

     for (int i = 0; i <= n; i++)
     {
          if (coeffs[i] == 0)
               continue; // Skip zero terms completely

          // Add a '+' before positive numbers, except for the very first printed term
          if (!first && coeffs[i] > 0)
               cout << "+";

          cout << coeffs[i]; // Print the actual coefficient (e.g., 1, -5, 4)

          // Print 'x^power' for everything except the final constant term
          if (n - i > 0)
               cout << "x^" << (n - i);

          first = false;
     }
     cout << "=0" << endl;
}

// Secant method modified for the specific class work requirements
void SECANT_METHOD(double x0, double x1, const vector<double> &coeffs, int root_idx)
{
     double E = 1e-3;
     double x_prev = x0;
     double xn = x1;
     int itr = 0;

     // The loop checks the condition before running.
     // Pass 1 safely uses the initial bounds (x1 and x0) to authorize entry.
     while (abs(xn - x_prev) >= E || abs(f(xn, coeffs)) >= E)
     {
          itr++;
          double f_prev = f(x_prev, coeffs);
          double f_curr = f(xn, coeffs);

          // Safety break to avoid division by zero
          if (abs(f_curr - f_prev) < 1e-12)
          {
               break;
          }

          // Calculate the new root directly inside the loop
          double x_next = xn - f_curr * ((xn - x_prev) / (f_curr - f_prev));

          // Shift the variables forward for the next condition check
          x_prev = xn;
          xn = x_next;
     }

     // Print results once the loop terminates
     cout << "Root " << root_idx << ": " << fixed << setprecision(5) << xn << endl;
     cout << "Search interval for root " << root_idx << "=[" << x0 << "," << x1 << "]" << endl;
     cout << "Iteration needed for the root " << root_idx << "= " << itr << endl
          << endl;
}

int main()
{
     int n;
     cout << "No. of degree of the equation: ";
     cin >> n;

     vector<double> coeffs(n + 1);
     cout << "Coefficients of the equation (from a_n to a_0): ";
     for (int i = 0; i <= n; i++)
     {
          cin >> coeffs[i];
     }

     cout << "Print the function ";
     print_polynomial(coeffs);
     cout << endl;

     // Calculate |x_max| = 1 + max(|a_i / a_n|)
     double max_ratio = 0.0;
     double a_n = coeffs[0];
     for (int i = 1; i <= n; i++)
     {
          double current_ratio = abs(coeffs[i] / a_n);
          if (current_ratio > max_ratio)
          {
               max_ratio = current_ratio;
          }
     }
     double x_max = 1.0 + max_ratio;

     // Search interval [-|x_max|, |x_max|]
     double step_size = 0.45;
     double a = -x_max;
     int root_count = 1;

     while (a < x_max)
     {
          double b = a + step_size;
          if (b > x_max)
               b = x_max; // Prevent overshooting the upper bound

          // Check for sign change to identify intervals containing a root
          if (f(a, coeffs) * f(b, coeffs) < 0)
          {
               SECANT_METHOD(a, b, coeffs, root_count);
               root_count++;
          }
          a = b;
     }

     if (root_count == 1)
     {
          cout << "No roots found in the calculated interval." << endl;
     }

     return 0;
}