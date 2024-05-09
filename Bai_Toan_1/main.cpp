#include <bits/stdc++.h>
using namespace std;

int n, k;
string s;

signed main(){
    for(int i = 1; i <= 10; ++i){
///     Setup for input and output file
        string file_in = "TEST/test", file_out = "TEST/test";
        file_in = file_in + to_string(i) + ".inp";
        file_out = file_out + to_string(i) + ".out";
        const char* file_in_cstr = file_in.c_str();
        const char* file_out_cstr = file_out.c_str();
        freopen(file_in_cstr, "r", stdin);
        freopen(file_out_cstr, "w", stdout);

        cin >> n >> k;
        for(int j = 1; j <= n; ++j){
            cin >> s;
        }
    }
}
