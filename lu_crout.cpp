#include <bits/stdc++.h>
using namespace std;


int n;


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
