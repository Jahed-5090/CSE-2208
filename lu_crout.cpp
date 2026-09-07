#include <bits/stdc++.h>
using namespace std;

/*
 * LU DECOMPOSITION METHOD -- CROUT'S METHOD (Triangularisation Method)
 * -----------------------------------------------------------------------
 * A = L * U, where:
 *   L : lower triangular, GENERAL diagonal (l11, l22, l33, ... are unknowns)
 *   U : upper triangular, UNIT diagonal   (u11 = u22 = u33 = ... = 1)
 *
 * This is the opposite convention from Doolittle's method (which fixes
 * L's diagonal to 1 instead). Crout's method is the one used in this
 * lecture.
 *
 * FOUR STEPS, EVERY TIME (per the slide "Four steps, every time"):
 *   Step 1: Write A = LU -- set up L and U in Crout form, with the
 *           unknown entries as symbols.
 *   Step 2: Multiply and compare -- carry out L x U and equate each
 *           entry to the matching entry of A. Solve the resulting
 *           equations in order: first row of A, then second, then third.
 *   Step 3: Forward substitution -- solve L Z = B from the top down to
 *           obtain the intermediate vector Z.
 *   Step 4: Back substitution -- solve U X = Z from the bottom up to
 *           obtain x, y, z (the final solution).
 *
 * NOTE (from the slide): Steps 1 and 2 depend only on A. If the
 * right-hand side B changes, you only need to repeat Steps 3 and 4.
 *
 * GENERAL FORMULAS for an n x n system (generalising the slide's
 * row-by-row 3x3 equations "l11 = a11", "l11*u12 = a12", ... ):
 *
 *   For each column j = 0 .. n-1:
 *     For i = j .. n-1:
 *         L[i][j] = A[i][j] - sum_{k=0}^{j-1} L[i][k] * U[k][j]
 *     U[j][j] = 1
 *     For i = j+1 .. n-1:
 *         U[j][i] = ( A[j][i] - sum_{k=0}^{j-1} L[j][k] * U[k][i] ) / L[j][j]
 *
 * This computes L's column j (using previously found columns), then
 * U's row j (using L[j][j] just computed) -- exactly mirroring how the
 * slide solves "first row of A", "second row of A", "third row of A"
 * in order, since each new unknown only depends on ones already found.
 */

int n;

// Step 1 + Step 2: build L and U by equating L*U with A, row by row
void decompose(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U)
{
    for (int j = 0; j < n; j++)
    {
        // --- column j of L (l_ij for i = j..n-1) ---
        for (int i = j; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[i][k] * U[k][j];
            L[i][j] = A[i][j] - sum;
        }

        // Crout's convention: U's diagonal is fixed at 1
        U[j][j] = 1.0;

        if (fabs(L[j][j]) < 1e-12)
        {
            cout << "Zero pivot encountered at L[" << j << "][" << j
                 << "] -- decomposition failed (needs pivoting)." << endl;
            exit(1);
        }

        // --- row j of U (u_ji for i = j+1..n-1) ---
        for (int i = j + 1; i < n; i++)
        {
            double sum = 0.0;
            for (int k = 0; k < j; k++)
                sum += L[j][k] * U[k][i];
            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }
}

// Step 3: Forward substitution, solve L Z = B (top down)
vector<double> forwardSubstitution(vector<vector<double>> &L, vector<double> &B)
{
    vector<double> Z(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int k = 0; k < i; k++)
            sum += L[i][k] * Z[k];
        Z[i] = (B[i] - sum) / L[i][i];
    }
    return Z;
}

// Step 4: Back substitution, solve U X = Z (bottom up)
vector<double> backSubstitution(vector<vector<double>> &U, vector<double> &Z)
{
    vector<double> X(n, 0.0);
    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int k = i + 1; k < n; k++)
            sum += U[i][k] * X[k];
        X[i] = Z[i] - sum;   // U[i][i] == 1, so no division needed
    }
    return X;
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
    vector<double> B(n);

    cout << "Enter matrix A (" << n << "x" << n << "), row by row:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    cout << "Enter vector B (" << n << " values):\n";
    for (int i = 0; i < n; i++)
        cin >> B[i];

    // Step 1 + Step 2: A = L * U
    decompose(A, L, U);

    cout << "\n--- Decomposition Result ---\n";
    printMatrix("L", L);
    printMatrix("U", U);

    // Step 3: L Z = B  (forward substitution)
    vector<double> Z = forwardSubstitution(L, B);
    cout << "Intermediate vector Z = [ ";
    for (double z : Z) cout << z << " ";
    cout << "]\n\n";

    // Step 4: U X = Z  (back substitution)
    vector<double> X = backSubstitution(U, Z);

    cout << "--- Solution ---\n";
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << X[i] << endl;

    return 0;
}

/*
 * ADDING PARTIAL PIVOTING (robustness improvement, not required by the
 * basic algorithm above): before eliminating column j, swap the current
 * row with whichever row below it has the largest |A[row][j]|. This
 * avoids dividing by a zero or tiny pivot L[j][j], and keeps the method
 * numerically stable for ill-conditioned matrices. Track the row swaps
 * in a permutation vector/matrix P, so the factorisation becomes
 * P*A = L*U instead of plain A = L*U.
 */
