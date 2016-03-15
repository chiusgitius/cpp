//chiu takae 3/15
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const double T = 100.;
const double dt = 0.01;
const double a[3] = {10., 20., 30.}; //default 10., 20., 30

class func_3var{
private:
    double p1, p2, p3, q1, q2, q3;
public:
    func_3var(double p1, double p2, double p3, double q1 = 0, double q2 = 0, double q3 = 0);
    double func(double t1, double y1, double y2, double y3){
        return p1 * y1 + p2 * y2 + p3 * y3 + q1 * y1 * y1 + q2 * y1 * y2 + q3 * y1 * y3;
    }
};

func_3var::func_3var(double a1, double a2, double a3, double b1, double b2, double b3){
    p1 = a1;
    p2 = a2;
    p3 = a3;
    q1 = b1;
    q2 = b2;
    q3 = b3;
}

func_3var solvefunc[3] = { // Lorentz equation
    func_3var(- 10., 10., 0.),
    func_3var(28., - 1., 0., 0., 0., -1.),
    func_3var(0., 0., - 8. / 3, 0., 1., 0.)
};

/* *default*
    func_3var(- 10., 10., 0.),
    func_3var(28., - 1., 0., 0., 0., -1.),
    func_3var(0., 0., - 8. / 3, 0., 1., 0.)
*/

void newyrk(double t1, double (&y)[3]){ // 配列の参照
    double k1[4], k2[4], k3[4], k4[4];
    for(auto i = 0; i < 3; i++){
        k1[i] = solvefunc[i].func(t1, y[0], y[1], y[2]); //vector クラス使えばもっとらくにかけそう
    }
    for(auto i = 0; i < 3; i++){
        k2[i] = solvefunc[i].func(t1 + dt / 2, y[0] + dt * k1[i] / 2., y[1] + dt * k1[i] / 2., y[2] + dt * k1[i] / 2.);
    }
    for(auto i = 0; i < 3; i++){
        k3[i] = solvefunc[i].func(t1 + dt / 2, y[0] + dt * k2[i] / 2., y[1] + dt * k2[i] / 2., y[2] + dt * k2[i] / 2.);
    }
    for(auto i = 0; i < 3; i++){
        k4[i] = solvefunc[i].func(t1 + dt, y[0] + dt * k3[i], y[1] + dt * k3[i], y[2] + dt * k3[i]);
    }
    for(auto i = 0; i < 3; i++){
        y[i] = (y[i] + dt * (k1[i] + 2. * k2[i] + 2. * k3[i] + k4[i]) / 6.);
    }
}

// double theoretical(double t){
// }

int main(){
    
	double t = 0.; 
	
	double y[3];
    for(auto i = 0; i < 3; i++){
        y[i] = a[i];
    }
    
//	double theo = theoretical(t);

    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);
        
    for(auto i = 0; t < T; i++){
		t = i * dt;
        
        cout << t << " " << y[0] << " " << y[1] << " " << y[2] << endl;
        
		newyrk(t, y);
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
