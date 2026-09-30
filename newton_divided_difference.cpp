#include <bits/stdc++.h>
using namespace std;

/*
 * NEWTON'S DIVIDED DIFFERENCE INTERPOLATION
 * -----------------------------------------------------------------------
 * Works for EQUAL or UNEQUAL x spacing (unlike Forward/Backward, which
 * both require equally spaced x). The slide's own worked example even
 * feeds the points in a non-sorted x order (1, 4, 6, 5) -- the method
 * doesn't care, it just uses whatever order the points are given in.
 *
 *   f[xi]          = f(xi)
 *   f[xi, xj]       = ( f(xi) - f(xj) ) / (xi - xj)
 *   f[xi, xj, xk]   = ( f[xi,xj] - f[xj,xk] ) / (xi - xk)
 *   ... and so on, recursively.
 *
 *   f(x) = f(x0) + (x-x0)*f[x1,x0]
 *                + (x-x0)(x-x1)*f[x2,x1,x0]
 *                + (x-x0)(x-x1)(x-x2)*f[x3,x2,x1,x0] + ...
 *
 * POLYNOMIAL RETRIEVAL: this method is already the most natural of the
 * three to retrieve as a plain polynomial in x, since each term is
 * already a literal product of (x - xi) factors -- no u/v substitution
 * needed like Forward/Backward. We just multiply those factors out with
 * the same multiplyLinear/addScaled helpers.
 */

vector<double> multiplyLinear(vector<double> &poly, double a, double b)
{
    vector<double> result(poly.size() + 1, 0.0);
    for (size_t i = 0; i < poly.size(); i++)
    {
        result[i]     += poly[i] * b;
        result[i + 1] += poly[i] * a;
    }
    return result;
}

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
        if (fabs(c) < 1e-9) continue;
        if (!first)
        {
            cout << (c >= 0 ? " + " : " - ");
            c = fabs(c);
        }
        else
        {
            if (c < 0) { cout << "-"; c = fabs(c); }
            first = false;
        }
        cout << fixed << setprecision(6) << c;
        if (i > 0) cout << "*x";
        if (i > 1) cout << "^" << i;
    }
    if (first) cout << "0";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter " << n << " x values (equal or unequal spacing, any order):\n";
    for (int i = 0; i < n; i++) cin >> x[i];
    cout << "Enter " << n << " corresponding y = f(x) values:\n";
    for (int i = 0; i < n; i++) cin >> y[i];

    // ---- build the divided difference table ----
    // dd[i][0] = f(xi); dd[i][j] = ( dd[i+1][j-1] - dd[i][j-1] ) / ( x[i+j] - x[i] )
    vector<vector<double>> dd(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) dd[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            dd[i][j] = (dd[i + 1][j - 1] - dd[i][j - 1]) / (x[i + j] - x[i]);

    cout << "\nDivided Difference Table:\n";
    for (int i = 0; i < n; i++)
    {
        cout << setw(10) << x[i] << setw(14) << dd[i][0];
        for (int j = 1; j < n - i; j++)
            cout << setw(14) << dd[i][j];
        cout << endl;
    }

    double xVal;
    cout << "\nEnter the x value to interpolate at: ";
    cin >> xVal;

    // ---- evaluate f(xVal) using the top row of the table, dd[0][k] ----
    double result = dd[0][0];
    double term = 1.0;
    for (int k = 1; k < n; k++)
    {
        term *= (xVal - x[k - 1]);
        result += term * dd[0][k];
    }

    cout << "\nInterpolated value at x = " << xVal << " is y = " << result << endl;

    // ---- polynomial retrieval ----
    vector<double> poly = { dd[0][0] };
    vector<double> termPoly = { 1.0 };

    for (int k = 1; k < n; k++)
    {
        // multiply termPoly by (x - x[k-1])
        termPoly = multiplyLinear(termPoly, 1.0, -x[k - 1]);
        addScaled(poly, termPoly, dd[0][k]);
    }

    cout << "\nRetrieved interpolating polynomial:\n";
    printPolynomial(poly);

    return 0;
}
