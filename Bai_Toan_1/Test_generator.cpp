#include <bits/stdc++.h>
#include <random>
using namespace std;

int n, length, k;

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
            n = get(7, 20), k = get(2, n-1);
            cout << n << ' ' << k << endl;
            for(int j = 1; j <= n; ++j){
                length = get(5, 10);
                while(length--){
                    cout << char('a' + get(0, 4));
                }
                cout << '\n';
            }
        }
        else{
            n = get(50, 100), k = get(20, n - 10);
            cout << n << ' ' << k << endl;
            for(int j = 1; j <= n; ++j){
                length = get(100, 1000);
                while(length--){
                    cout << char('a' + get(0, 25));
                }
                cout << '\n';
            }
        }
    }
}
