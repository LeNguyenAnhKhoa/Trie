# Danh mục nội dung
- [I. GIỚI THIỆU](#i-giới-thiệu)
- [II. CẤU TRÚC CÂY](#ii-cấu-trúc-cây)
- [III. CÀI ĐẶT](#iii-cài-đặt)
- [IV. ỨNG DỤNG](#iv-ứng-dụng)
    - [1. Bài toán 1](#1-bài-toán-1)
    - [2. Bài toán 2](#2-bài-toán-2)
    - [3. Bài toán 3](#3-bài-toán-3-query-on-strings---codechef)
    - [4. Bài toán 4](#4-bài-toán-4-voxor---vnspoj)
- [V. Bài tập](#v-bài-tập-thêm)
# I. GIỚI THIỆU

Ngày nay, với sự phát triển của công nghệ thông tin, dữ liệu ngày càng trở nên khổng lồ và phức tạp. Việc quản lý và xử lý dữ liệu hiệu quả là một vấn đề quan trọng trong nhiều lĩnh vực khác nhau. Một trong những giải pháp hiệu quả cho vấn đề này là sử dụng cấu trúc dữ liệu **Trie**.

**Trie** là một cấu trúc dữ liệu dạng cây được dùng để lưu trữ và xử lý một tập các xâu. Do tính chất dễ hiểu và dễ cài đặt nên **Trie** được sử dụng rất phổ biến hiện nay.

Các thao tác trên **Trie** bao gồm:
- Thêm 1 xâu vào tập hợp
- Xóa 1 xâu khỏi tập hợp
- Kiểm tra xâu có nằm trong tập hợp không

Ưu điểm: Tìm kiếm chuỗi nhanh chóng, thao tác hiệu quả và tiết kiệm bộ nhớ khi lưu trữ các chuỗi có chung tiền tố   


# II. CẤU TRÚC CÂY

<center>
<img src = "https://i.imgur.com/gZNzUnJ.png">
</center>

**Ý tưởng**: Mỗi đường đi từ gốc đến một nút bất kì sẽ là tiền tố của một xâu. Như vậy, việc lưu trữ các xâu có tiền tố giống nhau trở nên rất hiệu quả.

Trong **Trie**, mỗi cạnh được gán một kí tự và đường đi từ gốc tới đỉnh biểu diễn xâu được cấu tạo từ các cạnh trên đường đi đó. Ví dụ:
- Đỉnh `9`: biểu diễn xâu `bcd`
- Đỉnh `3`: biểu diễn xâu `abc`

Gọi `child(u, c)` là đỉnh con của $u$ được nối bằng cạnh có kí tự $c$, hoặc bằng $NULL$ nếu không tồn tại đỉnh con. Ta chỉ cần lưu mảng `child` với mỗi đỉnh để duy trì cấu trúc của **Trie**. Trong hình trên `child(1, 'b') = 2`, `child(5, 'b') = -1`, `child(5, 'a') = 7`.

# III. CÀI ĐẶT

Để tối ưu cho thao tác **tìm xâu** và thao tác **xóa xâu**, với mỗi đỉnh ngoài mảng `child` ta cần lưu thêm 2 biến:
- `cnt(u)`: số lượng xâu có tiền tố tại đỉnh $u$.
- `leaf(u)`: số lượng xâu kết thúc tại $u$.

Đầu tiên ta khai báo `Node` là kiểu dữ liệu cho mỗi đỉnh. Trong `Node` ta định nghĩa mảng `child` với giá trị khởi điểm là $NULL$, `leaf` và `cnt` đều bằng $0$ nghĩa là giá trị của khởi điểm của 1 đỉnh mới hoàn toàn. Ta lấy `root` chính là gốc của cây.

```cpp
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
}
```

Đối với thao tác thêm xâu, ta sẽ đi từ `root` đến các đỉnh khác với đường đi là kí tự hiện tại của xâu, nếu không tồn tại đường đi ta chỉ cần tạo đường đi mới.

```cpp
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
```
Đối với thao tác tìm xâu, ta sẽ đi từ root đến các đỉnh khác theo kí tự hiện tại của xâu và đối với đỉnh cuối ta cần kiểm tra `leaf(u) > 0`. Nếu trên đường đi không tồn tại cạnh ta trả về `false`.

```cpp
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
```

Đối với thao tác xóa xâu, trước tiên ta cần kiểm tra xâu có đang trong tập hợp hay không bằng thao tác `find_string`. Tiếp theo ta vẫn đi từ `root` qua các kí tự nhưng ở mỗi kí tự ta lần lượt giảm `cnt` và `leaf`. Nếu `cnt = 0` ta có thể loại bỏ hoàn toàn đỉnh này ra khỏi cây.

```cpp
#define SZ(x) (int)((x).size())
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
```

<details>

<summary>Full code</summary>

```cpp
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
        Node* p = root;
        for (auto f : s){
            int c = f - 'a';
            if(p->child[c] == NULL)return false;
            p = p->child[c];
        }
        return (p->leaf > 0);
    }

    bool delete_(Node* p, string& s, int i){
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
        if(find_string(s) == false)return;

        delete_(root, s, 0);
    }
};
```

</details>

# IV. ỨNG DỤNG

Trie tuy đơn giản nhưng lại có rất nhiều ứng dụng khác nhau. Ta sẽ đi qua các bài toán cụ thể để hiểu thêm về hiệu quả của CTDL này.

**Lưu ý:** Các bạn có thể tải repo này về và làm vào file `main.cpp` của bài 1 và 2 sau đó chạy file `checker.cpp` để so sánh với đáp án.

## 1. Bài toán 1: 

**Đề bài**: Cho $n$ xâu kí tự. Tìm xâu kí tự có thứ tự từ điển thứ $k$.

### Sample Input:
```
5 3
aacb
daec
abcc
bbaa
bcab
```

### Sample Output:
```
bbaa
```

**Lời giải**: Tứ đỉnh gốc ta sẽ đi ưu tiên qua cách cạnh có thứ tự từ điển từ bé đến lớn ($a$ - $z$). Do ta lưu biến $cnt$ nên với mỗi cạnh ta kiểm tra xem `k <= cnt` hay không:
- `k <= cnt`: Kí tự tiếp theo chính là cạnh ta đang xét và ta sẽ đi qua cạnh này
- `k > cnt`: Số lượng xâu khi ta qua cạnh này nhỏ hơn $k$ nên ta sẽ duyệt sang cạnh tiếp theo và gán $k = k - cnt$.

Tiếp tục quá trình này đến lúc số lượng xâu kết thúc tại đỉnh hiện tại lớn hơn hoặc bằng k thì dừng (k <= leaf).

<details>
<summary>Code</summary>

```cpp
string find_kth_string(int k) {
/*
        Find the k-th string
        Parameters
        ----------
        k: int
            input integer

        Returns
        s: str
            The k-th string
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
```
</details>

## 2. Bài toán 2: 
**Đề bài**: Cho $n$ số nguyên dương và $q$ truy vấn, với mỗi truy vấn cho số nguyên dương $x$. Hãy tìm giá trị `xor` lớn nhất của x với 1 số trong $n$ số nguyên đã cho.

### Sample Input:
```
5 3
1 3 7 2 5
1
2
3
```

### Sample Output:
```
6
7
6
```
**Giải thích**:
- Số $1$ có giá trị xor cao nhất là $6$ do `1^7 = 6`
- Số $2$ có giá trị xor cao nhất là $7$ do `2^5 = 7`
- Số $3$ có giá trị xor cao nhất là $6$ do `3^5 = 6`

**Lời giải**:  Với mỗi số nguyên dương ta có thể biểu diễn ở dạng nhị phân 30 bit (đánh số từ 0 đến 29). Giả sử mỗi chuỗi bit là 1 xâu kí tự ta có thể xây dựng $trie$ trên tập các xâu. Ta dễ thấy được trie lúc này có dạng cây nhị phân.

<center>
<img width="647" alt="Capture" src="https://github.com/LeNguyenAnhKhoa/Trie/assets/81629306/1408b815-763d-40cd-a38c-5711d65d2322">
</center>

Ta lần lượt duyệt các bit của $x$ đồng thời kiểm tra đường đi tiếp theo trên cây có tồn tại bit ngược với bit hiện tại đang xét hay không. Nếu có ta đi qua đỉnh tiếp theo trên Trie thông qua cạnh đó và cập nhật đáp án, nếu không thì ta bắt buộc đi theo đường đi còn lại.

Hình trên cho thấy truy vấn khi `x = 3` với hệ nhị phân là `010`. Giả sử $p$ là đỉnh hiện tại của cây (p = 0), $res$ là giá trị xor lớn nhất (res = 0), gọi $i$ là bit hiện tại đang duyệt và $b$ là giá trị bit hiện tại của $x$. Ta cần duyệt $i$ giảm dần do ta sẽ đi theo đường ưu tiên giá trị lớn hơn trước.
- `i = 2`: b = 0, do có đường đi giá trị $1$ nên ta sẽ đi đường này, `p = 7` và `res = res + 2^i = 4`
- `i = 1`: b = 1, do có đường đi giá trị $0$ nên ta sẽ đi đường này, `p = 11` và `res = res + 2^i = 6`
- `i = 0`: b = 0, do không có đường đi giá trị $1$ nên ta sẽ đi đường giá trị $0$, `p = 12`. Do ta không đi được đường có giá trị ngược lại nên tại đây ta không cập nhật $res$

<details>

<summary>Code</summary>

```cpp
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
```

</details>

## 3. Bài toán 3: [Query On Strings - CODECHEF](https://www.codechef.com/problems/NPLFLF)

**Đề bài:** Cho $q$ truy vấn, mỗi truy vấn thuộc 1 trong 3 loại:
- `q = 1`: Thêm xâu $s$ vào tập các xâu
- `q = 2`: Kiểm tra xem có ít nhất $k$ xâu cùng có hậu tố chung độ dài $l$ hay không
- `q = 3`: Xóa xâu khỏi tập hợp

### Sample Input:
```
9
1 aba
1 accba
2 2 2
2 2 3
1 aaaa
1 ababa
2 3 2
3 1
2 3 2
```

### Sample Output:
```
YES
NO
YES
NO
```

**Lời giải:** 
- Trước tiên ta cần đảo ngược các xâu lại, sau đó mới thêm vào Trie. Ta đã biết cách làm truy vấn `q = 1` và `q = 3`, đối với truy vấn `q = 2` ta chỉ cấn xét các đỉnh có `cnt >= k`. 
- Nếu ta đi đến đỉnh nào có độ dài l ta sẽ kết thúc chương trình và trả về True ngược lại trả về False.

```cpp
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
```

## 4. Bài toán 4: [VOXOR - VNSPOJ](https://oj.vnoi.info/problem/voxor)

**Lời giải:** 
- Trước tiên ta xây dựng trie dựa vào các bit như [Bài toán 2](#2-bài-toán-2). 
- Xét truy vấn tìm số lớn thứ $k$. Khi duyệt trên cây ta ưu tiên đi qua đường số 1 trước. Nếu số lượng số trên đường số 1 quá ít ta giảm k đi và đi qua đường số 0. Với mỗi lần đi qua đường số 1 ta cộng res thêm `2^i`.

```cpp
int get_k_th(int k){
/*
    Find the k-largest number
    -------------------------
    Returns
    res: int
        k-largest number
*/
    Node* p = root;
    int res = 0;
    for(int i = 29; i >= 0; --i){
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
    return res;
}
```

- Đối với truy vấn xor tất cả với $x$, ta sẽ xor tất cả các giá trị của x lại. Ta lần lượt duyệt các bit của x, ta chỉ quan tâm đến các `bit = 1` vì khi đó giá trị mảng A sẽ thay đổi.
- Nếu bit nào bằng 1 thì thay vì ưu tiên đường số 1 như trên, ta chỉ cần ưu tiên đường số 0 là được. 

<details>

<summary>Code</summary>

```cpp
int get(int k, int X){
/*
    Find the k-largest number
    Parameters
    X: int
        xor of all number of query xor
    ------------------------
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
```

</details>

# V. Bài tập thêm

[SPOJ - Ada and Indexing](https://www.spoj.com/problems/ADAINDEX/)

[SPOJ - Try to complete](https://www.spoj.com/problems/TRYCOMP/)

[Codeforces 948D](http://codeforces.com/problemset/problem/948/D)

[VOJ – ORDERSET](http://vn.spoj.com/problems/ORDERSET/) (Khuyến khích làm bằng Trie dù chạy không đủ nhanh)

[SPOJ - x-Xor It!](https://www.spoj.com/problems/XORX/)

[VOJ – MEDIAN](https://vn.spoj.com/problems/MEDIAN/)
