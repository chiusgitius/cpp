//
//  main.cpp
//  sosu
//
//  Created by Chiu Takae on 2016/03/01.
//
//

#include <iostream>
using namespace std;

int shantei(int m){ //m が素数なら m 自身を、そうでなければ 0 を返す関数
    int hantei = m;
    if(m == 1){
        return 0;
    }else{
        for(int j = 2; j < m; j++){
            if(m % j == 0){
                hantei = 0;
            }
        }
        return hantei;
    }
}

int main() {
    int n;
    int i;
    cout << "正の整数を入力してください" << endl;
    cin >> n;
    if(n == 1){
        cout << n << "以下の素数はありません" << endl;
    }else{
        cout << n << "以下の素数は ";
        for(i = 2; i <= n; i++){
            if(shantei(i) != 0){
                cout << i << " ";
            }else{
            }
        }
        cout << "です";
    }
    return 0;
}
