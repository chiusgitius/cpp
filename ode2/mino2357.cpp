//書いてみた
//RK4 only
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const double T = 10.;
const double dt = 0.01;//dtは自分で明示的に決めれるようにしておいた方がよい
const double a = 1.;

double solvefunc(double x){
    return - 2. * x;
}

//自励系なのでこれでいい．もちろんtありでも良い
double newyrk(double yold){
    double k1 = solvefunc(yold               );
    double k2 = solvefunc(yold + dt * k1 / 2.);
    double k3 = solvefunc(yold + dt * k2 / 2.);
    double k4 = solvefunc(yold + dt * k3     );
    
    return yold + dt * (k1 + 2. * k2 + 2. * k3 + k4)/6.;
}

double theoretical(double t){
    return exp( - 2. * t);
}

int main(){
    
	double t = 0.; 
	
	double yrk  = a;
	double theo = theoretical(t);

    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);
        
    for(auto i = 0; t < T; i++){
		t = i * dt; 
        
        cout << t << " " << yrk << " " << theo << " " << abs(yrk - theo)/theo << endl;
        
		yrk  = newyrk(yrk); 
		theo = theoretical(t);
    } 
    
    return 0;
}

/*
結果はターミナルで
./a.out > data.dat
してdatファイルに書き込んで
gnuplotで可視化すればよい

コマンドは
gnuplot> plot "dat.dat" using 1:2 w l
gnuplot> replot "dat.dat" using 1:3 w l
でグラフが出る．
*/
