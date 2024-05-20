/// Submission at https://oj.vnoi.info/problem/voxor
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int)((x).size())
int X, n, q;
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

    int get(int k, int X){
/*
        Find the k-largest number
        Parameters
        X: int
            xor of all number of query xor
        -------------------------
        Returns
        res: int
            k-largest number
*/
        Node* p = root;
        int res = 0;
        for(int i = 29; i >= 0; --i){
            int j = X >> i & 1;
            if(j){
                if(p->child[0] != NULL){
                    if(p->child[0]->cnt >= k){
                        p = p->child[0];
                        res |= 1 << i;
                        continue;
                    }
                    else{
                        k -= p->child[0]->cnt;
                        p = p->child[1];
                        continue;
                    }
                }
                p = p->child[1];
            }
            else{
                if(p->child[1] != NULL){
                    if(p->child[1]->cnt >= k){
                        p = p->child[1];
                        res |= 1 << i;
                        continue;
                    }
                    else{
                        k -= p->child[1]->cnt;
                        p = p->child[0];
                        continue;
                    }
                }
                p = p->child[0];
            }
        }
        return res;
    }

}trie;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    #define task "c"
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        int x; cin >> x;
        trie.add(x);
    }
    while(q--){
        string s; cin >> s;
        int x; cin >> x;
        if(s[0] == 'F')cout << trie.get(x, X) << endl;
        else X ^= x;
    }
}
