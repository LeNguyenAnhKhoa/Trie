#include <bits/stdc++.h>
using namespace std;

int n, k;
string s;

#define SZ(x) (int)((x).size())
struct Trie{
    struct Node{
        Node* child[26];
        int leaf, cnt;

        Node(){
            for(int i = 0; i < 26; i++)child[i] = NULL;
            leaf = cnt = 0;
        }
    };

    Node* root;
    Trie(){
        root = new Node();
    };

    void add_string(string s){
/*
        Parameters
        ----------
        s: str
            input string
*/
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL)p->child[c] = new Node();
            p = p->child[c];
            p->cnt++;
        }
        p->leaf++;
    }

    string find_kth_string(int k) {
/*
        Find the k-th string
        Parameters
        ----------
        k: int
            input integer

        Returns
        s: str

*/
        string s = "";
        Node* p = root;

        while(1){
            if(p->leaf >= k) break;
            k -= p->leaf;

            for(int i = 0; i < 26; i++)if(p->child[i] != NULL){
                Node* nx = p->child[i];
                if (nx->cnt >= k){
                    s += char(i + 'a');
                    p = nx;
                    break;
                }
                k -= nx->cnt;
            }
        }

        return s;
    }

};

signed main(){
    for(int i = 1; i <= 10; ++i){
///     Setup for read input and write output file
        string file_in = "TEST/test", file_out = "TEST/test";
        file_in = file_in + to_string(i) + ".inp";
        file_out = file_out + to_string(i) + ".ans";
        const char* file_in_cstr = file_in.c_str();
        const char* file_out_cstr = file_out.c_str();
        freopen(file_in_cstr, "r", stdin);
        freopen(file_out_cstr, "w", stdout);

///     Add string to Trie
        Trie t;
        cin >> n >> k;
        for(int j = 1; j <= n; ++j){
            cin >> s;
            t.add_string(s);
        }

///     Process
        cout << t.find_kth_string(k);
    }
}
