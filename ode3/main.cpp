//chiu takae 3/12
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const double T = 2.;
const double dt = 0.3;//0.01 dat.dat , 0.3 dat2.dat に出力
const double a1 = 1.;
const double a2 = 0.;

double solvefunc1(double t1, double y1, double y2){
    static const double p1 = 0., p2 = 1.;
    return p1 * y1 + p2 * y2;
}

double solvefunc2(double t1, double y1, double y2){
    static const double p1 = -16., p2 = -10;
    return p1 * y1 + p2 * y2;
}

//double newyeu(double t1, double y1old, double y2old){
//    y1old = y1old + dt * solvefunc1(t1, y1old, y2old);
//    y2old = y2old + dt * solvefunc2(t1, y1old, y2old);
//}

void newyrk(double t1, double& y1old, double& y2old){
    double k1_1 = solvefunc1(t1,           y1old                 , y2old);
    double k1_2 = solvefunc2(t1,           y1old                 , y2old);
    double k2_1 = solvefunc1(t1 + dt / 2., y1old + dt * k1_1 / 2., y2old + dt * k1_2 / 2.);
    double k2_2 = solvefunc2(t1 + dt / 2., y1old + dt * k1_1 / 2., y2old + dt * k1_2 / 2.);
    double k3_1 = solvefunc1(t1 + dt / 2., y1old + dt * k2_1 / 2., y2old + dt * k2_2 / 2.);
    double k3_2 = solvefunc2(t1 + dt / 2., y1old + dt * k2_2 / 2., y2old + dt * k2_2 / 2.);
    double k4_1 = solvefunc1(t1 + dt,      y1old + dt * k3_1     , y2old + dt * k3_1);
    double k4_2 = solvefunc2(t1 + dt,      y1old + dt * k3_1     , y2old + dt * k3_2);
    
    y1old = (y1old + dt * (k1_1 + 2. * k2_1 + 2. * k3_1 + k4_1)/6.);
    y2old = (y2old + dt * (k1_2 + 2. * k2_2 + 2. * k3_2 + k4_2)/6.);
    
}

double theoretical(double t){
    return (4 * exp(- 2. * t) - exp(- 8. * t)) / 3;
}

int main(){
    
	double t = 0.; 
	
	double y1eu, y1rk;
	double y2eu, y2rk;
    y1eu = y1rk = a1;
    y2eu = y2rk = a2;
	double theo = theoretical(t);

    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);
        
    for(auto i = 0; t < T; i++){
		t = i * dt;
        
		theo = theoretical(t);
        cout << t << " " << y1rk << " " << theo << " " << abs(y1rk - theo)/theo << endl;
        
		newyrk(t, y1rk, y2rk);
    } 
    
    return 0;
}

/*

"ode1.eps"にグラフを出力:
gnuplot> plot "dat.dat" using 1:2 w l
gnuplot> replot "dat.dat" using 1:3 w l
gnuplot> set terminal postscript eps
gnuplot> set out "ode1.eps"
gnuplot> replot

*/
