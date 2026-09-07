#include <bits/stdc++.h>
using namespace std;

/*
 * LU DECOMPOSITION METHOD  (Doolittle's Algorithm)
 * -----------------------------------------------------------------------
 * Goal: Solve a linear system A x = b by first factoring
 *       A = L * U
 * where:
 *   L = lower-triangular matrix with 1's on the diagonal
 *   U = upper-triangular matrix
 *
 * Once A = L*U, solving A x = b becomes two easy triangular solves
 * instead of one hard general solve:
 *
 *   Step 1: Decompose A into L and U.
 *   Step 2: Solve L y = b for y using FORWARD substitution
 *           (L is lower-triangular, so y1 depends only on itself,
 *           y2 depends on y1, etc. -- solve top to bottom).
 *   Step 3: Solve U x = y for x using BACKWARD substitution
 *           (U is upper-triangular, so the last unknown falls out
 *           first, then the one above it, etc. -- solve bottom to top).
 *
 * Why decompose at all? Because once you have L and U, you can reuse
 * them to solve A x = b for MANY different b vectors very cheaply --
 * you don't need to redo the expensive elimination step every time,
 * only the two cheap triangular solves.
 *
 * FORMULAS (Doolittle's method, no pivoting):
 *   For i = 0 .. n-1:
 *     U[i][j] = A[i][j] - sum_{k=0}^{i-1} L[i][k]*U[k][j]      for j = i..n-1
 *     L[i][i] = 1
 *     L[j][i] = (A[j][i] - sum_{k=0}^{i-1} L[j][k]*U[k][i]) / U[i][i]   for j = i+1..n-1
 *
 * NOTE: This basic version has NO partial pivoting, so it will fail
 * (division by zero) if any pivot U[i][i] becomes 0 -- e.g. if a
 * diagonal entry of A is zero after elimination. For a numerically
 * robust general-purpose solver you would add row-swapping (partial
 * pivoting), which is noted at the end of this file.
 */

int n;

// Step 1: Decompose A into L (lower) and U (upper)
void decompose(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U)
{
    for (int i = 0; i < n; i++)
    {
        // --- Compute row i of U ---
        for (int j = i; j < n; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }

        // --- Compute column i of L ---
        L[i][i] = 1.0;  // Doolittle's convention: unit diagonal for L
        for (int j = i + 1; j < n; j++)
        {
            double sum = 0.0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * U[k][i];

            if (fabs(U[i][i]) < 1e-12)
            {
                cout << "Zero pivot encountered at U[" << i << "][" << i
                     << "] -- decomposition failed (needs pivoting)." << endl;
                exit(1);
            }
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

// Step 2: Forward substitution to solve L y = b
vector<double> forwardSubstitution(vector<vector<double>> &L, vector<double> &b)
{
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int k = 0; k < i; k++)
            sum += L[i][k] * y[k];
        y[i] = (b[i] - sum) / L[i][i];   // L[i][i] is always 1 here, kept for generality
    }
    return y;
}

// Step 3: Backward substitution to solve U x = y
vector<double> backwardSubstitution(vector<vector<double>> &U, vector<double> &y)
{
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int k = i + 1; k < n; k++)
            sum += U[i][k] * x[k];
        x[i] = (y[i] - sum) / U[i][i];
    }
    return x;
}

void printMatrix(const string &name, vector<vector<double>> &M)
{
    cout << name << " =\n";
    for (auto &row : M)
    {
        for (double v : row)
            cout << setw(10) << fixed << setprecision(4) << v;
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout << "Enter size of the system (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    vector<double> b(n);

    cout << "Enter matrix A (" << n << "x" << n << "), row by row:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter vector b (" << n << " values):\n";
    for (int i = 0; i < n; i++)
        cin >> b[i];

    // Step 1: A = L * U
    decompose(A, L, U);

    cout << "\n--- Decomposition Result ---\n";
    printMatrix("L", L);
    printMatrix("U", U);

    // Step 2: L y = b  (forward substitution)
    vector<double> y = forwardSubstitution(L, b);

    // Step 3: U x = y  (backward substitution)
    vector<double> x = backwardSubstitution(U, y);

    cout << "--- Solution ---\n";
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << x[i] << endl;

    return 0;
}

/*
 * ADDING PARTIAL PIVOTING (robustness improvement, not required by the
 * basic algorithm above):
 * Before eliminating column i, swap the current row with whichever row
 * below it (row i..n-1) has the largest |A[row][i]|. This avoids
 * dividing by a zero or tiny pivot, and keeps the method numerically
 * stable for ill-conditioned matrices. Track the row swaps in a
 * permutation vector/matrix P, so the factorization becomes P*A = L*U
 * instead of plain A = L*U.
 */
