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
};
