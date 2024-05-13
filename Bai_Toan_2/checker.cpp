#include <bits/stdc++.h>
using namespace std;
string s1, s2;
signed main(){
    for(int i = 1; i <= 10; ++i){
///     Compare file testi.out and testi.ans
        string filename = "TEST/test";
        string out = filename + to_string(i) + ".out";
        string ans = filename + to_string(i) + ".ans";
        ifstream file1(out);
        ifstream file2(ans);
        bool ok = 1;
        while(getline(file1, s1) && getline(file2, s2)){
            if(s1 != s2){
                ok = 0;
                break;
            }
        }
        if(ok){
            cout << "Test " << i << ": CORRECT!" << endl;
        }
        else cout << "Test " << i << ": WRONG!" << endl;
    }
}
