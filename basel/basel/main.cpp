//
//  main.cpp
//  basel
//
//  Created by Chiu Takae on 2016/03/04.
//
//

#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;


int main() {
    double sum;
    int n;
    const double p = M_PI * M_PI / 6;
    cout << setprecision(12);
    cout << "1/k^2 の k = 1 から n までの和を計算する" << endl;
    for(;;){
        cout << "n = " ;
        cin >> n ;
        sum = 0;
        for(int i = 1; i <= n; i++){
            sum += (double)1 / (i * i);
        }
        cout << "n" << '\t' << "sum" << '\t' << "pi^2/6" << '\t' << "相対誤差" << endl;
        cout << n << '\t' << sum << '\t' << p << '\t' << fabs(sum - p) / p  <<  endl;
    }
}

// *問題点*
// ・n = 10000 くらいで sum と相対誤差が inf になる -> setprecision(12)の追加で n = 100000 くらいが限界になった