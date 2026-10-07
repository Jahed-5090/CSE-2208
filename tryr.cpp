#include <bits/stdc++.h>
using namespace std;
int n;

double fact(int x)
{
     double ans = 1.0;

     for (int i = 2; i <= x; i++)
     {
          ans *= i;
     }
     return ans;
}

double divided(double target, vector<double> &x, vector<double> &y, vector<vector<double>> &diff)
{

     for(int i=0;i<n;i++) diff[i][0]=y[i] ; 

     for(int j=1;j<n;j++) {
          for(int i=0;i<n-j;i++) {
               diff[i][j] = (diff[i+1][j-1]-diff[i][j-1])/(x[i+j]-x[i]) ;
          }
     } 

     cout << "\nDivided Difference Table:\n";

     for(int i=0;i<n;i++) {
          cout << setw(10) << x[i] << setw(12) << y[i] ;
          for(int j=1;j<n-i;j++) {
               cout << setw(12) << diff[i][j] ;
          } cout << endl ;
     } cout << endl ;

     double result = diff[0][0] ; 
     double term = 1.0 ; 

     for(int i=1;i<n;i++) {
        term *= (target-x[i-1]);
        result += (term/fact(i))*diff[0][i] ;
     }

     cout << "result : " << result << endl ;
 
return result ;
}

int main()
{

     cout << "Enter the number of data points: ";
     cin >> n;

     cout << "Enter the X values : ";
     vector<double> x(n, 0), y(n, 0);

     for (int i = 0; i < n; i++)
     {
          cin >> x[i];
     }
     cout << "Enter the corresponding y values : ";
     for (int i = 0; i < n; i++)
     {
          cin >> y[i];
     }

     vector<vector<double>> diff(n, vector<double>(n, 0.0));

     double target;
     cout << "Enter the target x value : ";
     cin >> target;

     double res1 = divided(target, x, y, diff);

     return 0;
}

/*

4 3 5 7 9 180 150 120 90 4

*/