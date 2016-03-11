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

//可視化は後回しでコードの添削をする

//グローバル変数はなるべくなくす．数値計算だと，constなパラメータのみにする場合が多い
//t, yeu, yhe, yrk, theo, x　はグローバル変数にすべきでない．
const int N = 100; // 分点の数
const double T = 1.;
const double dt = T / N;
const double a = 1.;

double solvefunc(double t1, double x1){
    static const double c = -2.;
    return (c * x1);
}

double newyeu(double t1, double yold){
    return (yold + dt * solvefunc(t1, yold));
}

double newyhe(double t1, double yold){
    double k1 = solvefunc(t1, yold);
    double k2 = solvefunc(t1 + dt, yold + dt * k1);
    
    return(yold + dt * (k1 + k2)/2.);
}

double newyrk(double t1, double yold){
    double k1 = solvefunc(t1,          yold              );
    double k2 = solvefunc(t1 + dt / 2., yold + dt * k1 / 2.);
    double k3 = solvefunc(t1 + dt / 2., yold + dt * k2 / 2.);
    double k4 = solvefunc(t1 + dt,     yold + dt * k3    );
    
    return (yold + dt * (k1 + 2. * k2 + 2. * k3 + k4)/6.);
}

double theoretical(double t){
    return exp(- 2. * t);
}

int main() {
    
	double t = 0.; 
	//double yeu[N], yhe[N], yrk[N], theo[N];
	//動的に確保した方が良い
//	auto *x    = new double[N]; x is 何？
	auto *yeu  = new double[N];
	auto *yhe  = new double[N];
	auto *yrk  = new double[N];
	auto *theo = new double[N];

    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);
/*
	FILE *gp;
	gp = popen("gnuplot -persist", "w");
	fprintf(gp, "set tr [0:1.5]\n");
	fprintf(gp, "set yr [0:10]\n");
    fprintf(gp, "set grid\n");
*/

    //日本語は標準出力する必要はない．コードの冒頭に書いておけばよい．
    //cout << "solving y' = - 2 * y, y(0) = 1" << endl;
    
    // 変数分離法で解くと y = exp(-2t)
    
    //cout << "i" << '\t' << "オイラー法" << '\t' << "ホイン法" << '\t' << "ルンゲ＝クッタ法" << '\t' << "厳密解 y = exp(-2t)" << endl;
    yeu[0] = yhe[0] = yrk[0] = a;
    cout << t << '\t' << yeu[0] << '\t'  << yhe[0] << '\t' << yrk[0] << '\t' << theo[0] << endl;
        
	//fprintf(gp, "plot '-' w l lw 3\n");
    for(int i = 1; i < N; i++){
        t = i * dt;
        
		yeu[i]  = newyeu(t, yeu[i-1]);
        yhe[i]  = newyhe(t, yhe[i-1]);
        yrk[i]  = newyrk(t, yrk[i-1]);
        
		theo[i] = theoretical(t);
         
        cout << t << '\t' << yeu[i] << '\t'  << yhe[i] << '\t' << yrk[i] << '\t' << theo[i] << endl;
       /* 
        fprintf(gp, "%f %f \n", t, yeu[i]);
        fprintf(gp, "%f %f \n", t, yhe[i]);
        fprintf(gp, "%f %f \n", t, yrk[i]);
        fprintf(gp, "%f %f \n", t, theo[i]);
		*/
    } 
    //fprintf(gp, "e\n");
	//fflush(gp);

    //pclose(gp);
	
	//メモリの解放
	delete[] yeu;
	delete[] yhe;
	delete[] yrk;
	delete[] theo;

//	delete[] x;
    
    return 0;
}

// *課題*
// ・誤差の明確化
// ・i == 0 まわりがあまりスマートでない
// ・ちゃんと gnuplot で plot できてない（gnuplot を一ミリも理解できてないのがバレてしまう……）

//正しく計算はできていると思う．しかし，結果を配列に溜め込む必要はない．
