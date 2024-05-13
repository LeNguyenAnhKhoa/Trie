#include <bits/stdc++.h>
#include <random>
using namespace std;

int n, length, q;

int get(int l, int r){
    return l + rand() % (r - l + 1);
}

signed main(){
    /// setup random device
    srand(time(NULL));

    /// generate test
    for(int i = 1; i <= 10; ++i){
        string filename = "TEST/test";
        filename = filename + to_string(i) + ".inp";
        const char* filename_cstr = filename.c_str();
        freopen(filename_cstr, "w", stdout);

        if(i <= 7){
            n = get(7, 20), q = get(5, 10);
            cout << n << ' ' << q << endl;
            for(int j = 1; j <= n; ++j){
                cout << get(1, 31) << ' ';
            }
            cout << endl;
            for(int j = 1; j <= q; ++j){
                cout << get(1, 31) << endl;
            }
        }
        else{
            n = get(1e4, 1e5), q = get(1e4, 1e5);
            cout << n << ' ' << q << endl;
            for(int j = 1; j <= n; ++j){
                cout << get(1, 1000000000) << ' ';
            }
            cout << endl;
            for(int j = 1; j <= q; ++j){
                cout << get(1, 1000000000) << endl;
            }
        }
    }
}
