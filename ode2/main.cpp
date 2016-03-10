//
//  main.cpp
//  ode2
//
//  Created by Chiu Takae on 2016/03/10.
//
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

    const int N = 100; // 分点の数
    double t; 
    double yeu[N], yhe[N], yrk[N], theo[N];
    const double T = 1.;
    const double dt = T / N;
    const double a = 1.;
    int x[N];

double solvefunc(double t1, double x1){
    const double c = -2.;
    
    return (c * x1);
}

double newyeu(double t1, double yold){
    return(yold + dt * solvefunc(t1, yold));
}

double newyhe(double t1, double yold){
    double k1 = solvefunc(t1, yold);
    double k2 = solvefunc(t1 + dt, yold + dt * k1);
    
//  cout << k1 << endl;
    
    return(yold + dt * (k1 + k2)/2);
}

double newyrk(double t1, double yold){
    double k1 = solvefunc(t1, yold);
    double k2 = solvefunc(t1 + dt / 2, yold + dt * k1 / 2);
    double k3 = solvefunc(t1 + dt / 2, yold + dt * k2 / 2);
    double k4 = solvefunc(t1 + dt, yold + dt * k3);
    
    return(yold + dt * (k1 + 2 * k2 + 2 * k3 + k4)/6);
}

double theoretical(double t1){
    return exp(-2 * t1);
}

int main() {
    
    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);

	FILE *gp;
	gp = popen("gnuplot -persist", "w");
	fprintf(gp, "set tr [0:1.5]\n");
	fprintf(gp, "set yr [0:10]\n");
   	fprintf(gp, "set grid\n");


    
    cout << "solving y' = - 2 * y, y(0) = 1" << endl;
    
    // 変数分離法で解くと y = exp(-2t)
    
    cout << "i" << '\t' << "オイラー法" << '\t' << "ホイン法" << '\t' << "ルンゲ＝クッタ法" << '\t' << "y = exp(-2t)" << endl;
    yeu[0] = yhe[0] = yrk[0] = a;
        
	fprintf(gp, "plot '-' w l lw 3\n");
    for(int i = 0; i < N; i++){
        t = i * dt;
        if(i == 0){
            yeu[i] = yhe[i] = yrk[i] = theo[i] = a;
        }else{
            yeu[i] = newyeu(t, yeu[i-1]);
            yhe[i] = newyhe(t, yhe[i-1]);
            yrk[i] = newyrk(t, yrk[i-1]);
            theo[i] = theoretical(t);
        } 
        cout << i << '\t' << yeu[i] << '\t'  << yhe[i] << '\t' << yrk[i] << '\t' << theo[i] << endl;
        
        fprintf(gp, "%f %f \n", t, yeu[i]);
        fprintf(gp, "%f %f \n", t, yhe[i]);
        fprintf(gp, "%f %f \n", t, yrk[i]);
        fprintf(gp, "%f %f \n", t, theo[i]);
    } 
    fprintf(gp, "e\n");
	fflush(gp);

   pclose(gp);
    
    return 0;
}

// *課題*
// ・誤差の明確化
// ・i == 0 まわりがあまりスマートでない