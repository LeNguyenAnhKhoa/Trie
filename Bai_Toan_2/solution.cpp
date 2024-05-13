#include <bits/stdc++.h>
using namespace std;

int n, q;

#define SZ(x) (int)((x).size())
struct Trie{
    struct Node{
        Node* child[2];
        int leaf, cnt;

        Node(){
            child[0] = child[1] = NULL;
            leaf = cnt = 0;
        }
    };

    Node* root;
    Trie(){
        root = new Node();
    };

    void add(int x){
/*
        Parameters
        ----------
        x: int
            input integer
*/
        Node* p = root;
        for(int i = 29; i >= 0; --i){
            int b = x >> i & 1;
            if(p->child[b] == NULL)
                p->child[b] = new Node();
            p = p->child[b];
            p->cnt++;
        }
        p->leaf++;
    }

    int max_xor(int x) {
/*
        Find the maximum xor with x
        Parameters
        ----------
        x: int
            input integer

        Returns
        res: int

*/
        Node* p = root;
        int res = 0;
        for(int i = 29; i >= 0; --i){
            int b = x >> i & 1;
            if(p->child[!b] != NULL){
                res |= 1 << i;
                p = p->child[!b];
            }
            else p = p->child[b];
        }

        return res;
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

///     Add integer to Trie
        Trie t;
        cin >> n >> q;
        for(int j = 1; j <= n; ++j){
            int x; cin >> x;
            t.add(x);
        }

///     Process
        while(q--){
            int x; cin >> x;
            cout << t.max_xor(x) << endl;
        }
    }
}
