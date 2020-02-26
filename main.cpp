#include <iostream>
#include "fibo.h"

using namespace std;
using namespace boost;


int main() {


//    Fibo f{7}, s{15};
//
//    Fibo r = {"100000"};
//    cout << (r << 2) << endl;
//
//    cout<<f<<endl;

    cout << (Fibo("1001") ^ Fibo("1010")) << endl;

    int m = 20;
    for (int i = 0; i<=m ;i++) {
        for (int j=0; j<m; j++) {
//            if (Fibo(i) + Fibo(j) != Fibo(i+j))
                cout << Fibo(i) << " " << Fibo(j) << "" << Fibo(i) + Fibo(j) << " " << Fibo(i+j) << endl;
        }
    }
}


