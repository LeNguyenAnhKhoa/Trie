#include <bits/stdc++.h>
using namespace std;
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

    bool find_string(string s){
/*
        Check if the string s in Trie
        Parameters
        ----------
        s: str
            input string

        Returns
        True or False
*/
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL)return false;
            p = p->child[c];
        }
        return (p->leaf > 0);
    }

    bool delete_(Node* p, string& s, int i){
/*
        delete string s
        Parameters
        ----------
        p: Node pointer
            pointer of current vertex
        s: str
            input string
        i: int
            the current word is s[i]
        Returns
        True or False: Is the next vertex deleted
*/
        if(i != SZ(s)){
            int c = s[i] - 'a';
            bool deleted = delete_(p->child[c], s, i + 1);
            if(deleted)p->child[c] = NULL;
        }
        else p->leaf--;

        if(p != root){
            p->cnt--;
            if(p->cnt == 0) {
                delete(p);
                return true;
            }
        }
        return false;
    }

    void delete_string(string s) {
/*
        delete string s
        Parameters
        ----------
        s: str
            input string
*/
        if(find_string(s) == false)return;

        delete_(root, s, 0);
    }

    bool get(Node* p, int k, int l) {
/*
        Check if there at least k strings have prefix length l
        Parameters
        ----------
        k: int
            minimum number of strings needed
        l: int
            length of strings
        p: Node pointer
            current Node pointer on Trie
        Returns
        ok: boolean
            ok = 1: There at least k strings have prefix length l
            ok = 0: There are no k strings have prefix length l
*/
        if(l == 0)return true;
        bool ok = false;
        for(int i = 0; i < 26; ++i){
            if(p->child[i] != NULL && p->child[i]->cnt >= k){
                ok |= get(p->child[i], k, l-1);
                if(ok)break;
            }
        }
        return ok;
    }
}trie;
unordered_map<int, string> mp;
bool removed[100005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    for(int i = 1; i <= q; ++i){
        int t; cin >> t;
        if(t == 1){
            string s; cin >> s;
            reverse(s.begin(), s.end());
            mp[i] = s;
            trie.add_string(s);
        }
        else if(t == 2){
            int k, l; cin >> k >> l;
            if(trie.get(trie.root, k, l))puts("YES");
            else puts("NO");
        }
        else{
            int x; cin >> x;
            if(!removed[x]){
                removed[x] = 1;
                trie.delete_string(mp[x]);
            }
        }
    }
}
