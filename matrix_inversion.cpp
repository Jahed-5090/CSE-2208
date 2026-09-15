#include <bits/stdc++.h>
using namespace std;

/*
 * MATRIX INVERSION METHOD  (Solution of a System of Linear Algebraic Equations)
 * -----------------------------------------------------------------------
 * The two formulas behind the method:
 *     A^-1 = adj(A) / det(A)
 *     X    = A^-1 * B
 *
 * SIX STEPS, EVERY TIME (per the slide "Six steps from equations to answer"):
 *   Step 1: Convert to matrix form   -- write the system as A X = B.
 *   Step 2: Compute det(A)           -- expand along a row/column; if it
 *                                       is zero, STOP (the method does
 *                                       not apply -- A is not invertible).
 *   Step 3: Find the nine cofactors  -- (n*n for an n x n system) using
 *                                       C[i][j] = (-1)^(i+j) * M[i][j],
 *                                       where M[i][j] is the minor
 *                                       (delete row i, column j, take
 *                                       the determinant of what's left).
 *   Step 4: Write the adjoint        -- assemble the cofactor matrix,
 *                                       then TRANSPOSE it. adj(A) = C^T.
 *   Step 5: Form the inverse         -- divide every entry of the
 *                                       adjoint by det(A).
 *   Step 6: Final answer             -- multiply out X = A^-1 * B.
 *
 * NOTE (from the slide): Steps 2-5 build A^-1 and depend only on A --
 * if the right-hand side B changes, only Step 6 needs to be repeated.
 *
 * This implementation generalises the slide's 3x3 example to any n x n
 * system using recursive cofactor expansion for the determinant/minors.
 */

int n;

// Delete row `row` and column `col` from matrix M -- this is exactly
// the "Minor" building block from the slide: "Delete row i and column j
// from A. The determinant of the block left behind is the minor."
vector<vector<double>> deleteRowCol(vector<vector<double>> &M, int row, int col)
{
    int sz = M.size();
    vector<vector<double>> result;
    for (int i = 0; i < sz; i++)
    {
        if (i == row) continue;
        vector<double> newRow;
        for (int j = 0; j < sz; j++)
        {
            if (j == col) continue;
            newRow.push_back(M[i][j]);
        }
        result.push_back(newRow);
    }
    return result;
}

// Determinant by cofactor expansion along the first row (as the slide
// suggests: "Expand along the first row; check it is non-zero").
// Works for any size; base case is the trivial 1x1 determinant.
double determinant(vector<vector<double>> &M)
{
    int sz = M.size();

    if (sz == 1)
        return M[0][0];

    if (sz == 2)
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];

    double det = 0.0;
    for (int j = 0; j < sz; j++)
    {
        vector<vector<double>> minor = deleteRowCol(M, 0, j);
        double sign = (j % 2 == 0) ? 1.0 : -1.0;   // (-1)^(0+j)
        det += sign * M[0][j] * determinant(minor);
    }
    return det;
}

// Step 3: build the n x n matrix of cofactors,
// C[i][j] = (-1)^(i+j) * M_ij   (the "checkerboard" sign pattern)
vector<vector<double>> cofactorMatrix(vector<vector<double>> &A)
{
    vector<vector<double>> C(n, vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            vector<vector<double>> minor = deleteRowCol(A, i, j);
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            C[i][j] = sign * determinant(minor);
        }
    }
    return C;
}

// Step 4: adjoint = transpose of the cofactor matrix
vector<vector<double>> transpose(vector<vector<double>> &C)
{
    vector<vector<double>> T(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            T[j][i] = C[i][j];
    return T;
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
    vector<double> B(n);

    // Step 1: Convert to matrix form -- read A and B directly
    cout << "Enter matrix A (" << n << "x" << n << "), row by row:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter vector B (" << n << " values):\n";
    for (int i = 0; i < n; i++)
        cin >> B[i];

    // Step 2: Compute det(A)
    double det = determinant(A);
    cout << "\ndet(A) = " << det << endl;

    if (fabs(det) < 1e-12)
    {
        cout << "det(A) = 0 -- A is singular, the matrix inversion method "
             << "does not apply (no unique solution)." << endl;
        return 0;
    }

    // Step 3: Find the cofactors
    vector<vector<double>> C = cofactorMatrix(A);
    printMatrix("Cofactor matrix C", C);

    // Step 4: Write the adjoint (transpose of C)
    vector<vector<double>> adj = transpose(C);
    printMatrix("adj(A)", adj);

    // Step 5: Form the inverse, A^-1 = adj(A) / det(A)
    vector<vector<double>> Ainv(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Ainv[i][j] = adj[i][j] / det;
    printMatrix("A^-1", Ainv);

    // Step 6: Final answer, X = A^-1 * B
    vector<double> X(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
            sum += Ainv[i][j] * B[j];
        X[i] = sum;
    }

    cout << "--- Solution ---\n";
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << X[i] << endl;

    return 0;
}

/*
 * NOTE ON EFFICIENCY: the recursive cofactor-expansion determinant used
 * here is O(n!) -- perfectly fine for the small (e.g. 3x3) systems this
 * lecture uses by hand, but it becomes very slow for large n. For big
 * systems, LU Decomposition (see lu_crout.cpp / lu_doolittle.cpp) is
 * the practical choice -- computing a determinant/inverse that way is
 * only O(n^3). This is also why the slide calls Matrix Inversion "a
 * direct method" suited to small, hand-checkable systems.
 */