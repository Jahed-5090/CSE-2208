#include <bits/stdc++.h>
using namespace std;

/*
 * NEWTON'S FORWARD INTERPOLATION
 * -----------------------------------------------------------------------
 * Used when x is near the BEGINNING of the table (slide: "Newton's
 * Forward Interpolation"). Requires EQUALLY SPACED x values.
 *
 *   h  = x1 - x0  (common spacing)
 *   u  = (x - x0) / h
 *
 *   y = y0 + u*Dy0 + u(u-1)/2! * D^2y0 + u(u-1)(u-2)/3! * D^3y0 + ...
 *
 * where D^k y0 ("Delta^k y0") is the k-th forward difference, read off
 * the TOP-LEFT-TO-BOTTOM-RIGHT diagonal of the forward difference table
 * (Table 3 on the slide).
 *
 * POLYNOMIAL RETRIEVAL:
 * The formula above is a polynomial in u, and u itself is a LINEAR
 * function of x: u(x) = (1/h)*x - x0/h. So each product term
 * u(u-1)(u-2)...(u-k+1) is really a product of k linear factors in x,
 * of the form (a*x + b). Multiplying these out with plain polynomial
 * multiplication (see multiplyLinear/addScaled below) gives the full
 * expanded polynomial P(x) = c0 + c1*x + c2*x^2 + ... -- the same
 * polynomial the forward formula evaluates, just in standard form so
 * it can be reused, differentiated, plotted, etc. without redoing the
 * whole table lookup.
 */

// ---- polynomial helpers (ascending powers of x: poly[i] = coeff of x^i) ----

// multiply poly(x) by the linear factor (a*x + b)
vector<double> multiplyLinear(vector<double> &poly, double a, double b)
{
    vector<double> result(poly.size() + 1, 0.0);
    for (size_t i = 0; i < poly.size(); i++)
    {
        result[i] += poly[i] * b;
        result[i + 1] += poly[i] * a;
    }
    return result;
}

// poly += scale * term   (term may be a smaller-degree polynomial)
void addScaled(vector<double> &poly, vector<double> &term, double scale)
{
    if (term.size() > poly.size())
        poly.resize(term.size(), 0.0);
    for (size_t i = 0; i < term.size(); i++)
        poly[i] += scale * term[i];
}

void printPolynomial(vector<double> &poly)
{
    cout << "P(x) = ";
    bool first = true;
    for (int i = (int)poly.size() - 1; i >= 0; i--)
    {
        double c = poly[i];
        if (fabs(c) < 1e-9)
            continue;
        if (!first)
        {
            cout << (c >= 0 ? " + " : " - ");
            c = fabs(c);
        }
        else
        {
            if (c < 0)
            {
                cout << "-";
                c = fabs(c);
            }
            first = false;
        }
        cout << fixed << setprecision(6) << c;
        if (i > 0)
            cout << "*x";
        if (i > 1)
            cout << "^" << i;
    }
    if (first)
        cout << "0";
    cout << endl;
}

double factorial(int k)
{
    double f = 1.0;
    for (int i = 2; i <= k; i++)
        f *= i;
    return f;
}

int main()
{
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter " << n << " equally spaced x values:\n";
    for (int i = 0; i < n; i++)
        cin >> x[i];
    cout << "Enter " << n << " corresponding y = f(x) values:\n";
    for (int i = 0; i < n; i++)
        cin >> y[i];

    double h = x[1] - x[0];

    // ---- build the forward difference table (Table 3 on the slide) ----
    vector<vector<double>> diff(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = y[i];
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1];
        }
    }

    cout << "\nForward Difference Table:\n";
    for (int i = 0; i < n; i++)
    {
        cout << setw(10) << x[i] << setw(12) << diff[i][0];
        for (int j = 1; j < n - i; j++)
            cout << setw(12) << diff[i][j];
        cout << endl;
    }

    double xVal;
    cout << "\nEnter the x value to interpolate at: ";
    cin >> xVal;

    double u = (xVal - x[0]) / h;

    // ---- evaluate y using the forward formula, top diagonal diff[0][k] ----
    double result = diff[0][0];
    double term = 1.0;
    for (int k = 1; k < n; k++)
    {
        term *= (u - (k - 1));
        result += (term / factorial(k)) * diff[0][k];
    }

    cout << "\nu = (x - x0)/h = " << u << endl;
    cout << "Interpolated value at x = " << xVal << " is y = " << result << endl;

    // ---- polynomial retrieval ----
    vector<double> poly = {diff[0][0]}; // start with y0 (constant term)
    vector<double> termPoly = {1.0};    // running product, as a polynomial in x

    for (int k = 1; k < n; k++)
    {
        // multiply termPoly by (u - (k-1)), where u = (1/h)x - x0/h
        termPoly = multiplyLinear(termPoly, 1.0 / h, -x[0] / h - (k - 1));
        double coeff = diff[0][k] / factorial(k);
        addScaled(poly, termPoly, coeff);
    }

    cout << "\nRetrieved interpolating polynomial:\n";
    printPolynomial(poly);

    return 0;
}
