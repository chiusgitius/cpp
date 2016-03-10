//バーゼル問題
//自然数の二乗の逆数の和を計算する．
//1644年に Pietro Mengoli によって提起され，1735年にレオンハルト・オイラーによって解かれた．

#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

static constexpr size_t N = 10000000;
//const size_t N = 100;

//前から
template <typename T>
T basel_A(size_t n){
    T sum = T{};
    for(size_t i=1; i<n; ++i){
        sum += static_cast<T>(1./(i*i));
    }
    return sum;
}

//後ろから
template <typename T>
T basel_B(size_t n){
    T sum = T{};
    for(size_t i=n-1; i>0; --i){
        sum += static_cast<T>(1./(i*i));
    }
    return sum;
}


int main(){
    
    cout << fixed << setprecision(numeric_limits<double>::digits10 + 1);
    
    cout << sizeof(size_t);
    
    double a = basel_A<double>(N);
    cout << a << endl;
    
    double b = basel_B<double>(N);
    cout << b << endl;
    
    cout << endl;
    
    //円周率
    static constexpr double pi = acos(-1.);
    
    //絶対誤差評価
    cout << abs(pi - sqrt(6. * a)) << endl;
    cout << abs(pi - sqrt(6. * b)) << endl;
    
    std::cout << std::endl;
    
    //相対誤差評価
    cout << abs(pi - sqrt(6. * a))/pi << endl;
    cout << abs(pi - sqrt(6. * b))/pi << endl;
    
    return 0;
}