#include <bits/stdc++.h> 
using namespace std ;  
 

void gaussjordan(vector<vector<double>> &augmat,vector<double> &X,int n) {

    for(int j=0;j<n;j++) {
        double pivot = augmat[j][j] ; 

        for(int i=0;i<=n;i++) {
            augmat[j][i] /= pivot ;
        } 

        for(int i=0;i<n;i++) {
            if(j==i) continue;

            double ratio = augmat[i][j]/ augmat[j][j] ; 

            for(int k=0;k<=n;k++) {
                augmat[i][k]=augmat[i][k]-ratio*augmat[j][k];
            }


        }

    } 

    for(int i=0;i<n;i++) {
        X[i] = augmat[i][n] ;
    }



}



int main() { 

    
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {6, 11, 18, 27, 38};
    int n = 5; 

    const int degree = 2 ; 
    const int terms = degree+1 ; 

    double sumX[2*degree+1] = {0} ; 

    // calculating x^0+x^1+...x^degree


    for(int i=0;i<n;i++) {
        double power = 1 ; 
        for(int j=0;j<=2*degree;j++) {
          sumX[j] += power ;
          power *= x[i] ;
        }
    }

    // calculating x^0*y + x^1*y + ...

    double sumXY[degree + 1] = {0}; 
 
    for(int i=0;i<n;i++) {
        int power = 1 ; 
        for(int j=0;j<=degree;j++) {
            sumXY[j] += (power*y[i]) ;
            power *= x[i] ; 
        }
    }


    // creating augmented matrix 


    vector<vector<double>> augmat(terms,vector<double>(terms,0.0)) ; 


    for(int i=0;i<terms;i++) {
        for(int j=0;j<terms+1;j++) {
        augmat[i][j]=sumX[i+j] ;
        }
        augmat[i][terms]=sumXY[i] ;
    } 

    vector<double> X(n,0.0) ;
    gaussjordan(augmat,X,terms) ; 

    cout << "Fitted polynomial: y = "; 

    for(int i=0;i<terms;i++) {
        cout << X[i] ; 
        if(i>0) cout << " * X^" << i ; 
        if(i!=terms-1) cout << " + " ;

    } cout << endl ;

  

    return 0;
}