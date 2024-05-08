## Giới thiệu

**Trie** là một cấu trúc dữ liệu dạng cây được dùng để lưu trữ và xử lý một tập các xâu. Do tính chất dễ hiểu và dễ cài đặt nên **Trie** được sử dụng rất phổ biến hiện nay.

Các thao tác trên **Trie** bao gồm:
- Thêm 1 xâu vào tập hợp
- Xóa 1 xâu khỏi tập hợp
- Kiểm tra xâu có nằm trong tập hợp không

## Cấu trúc cây

<center>
<img src = "https://i.imgur.com/gZNzUnJ.png">
</center>

**Ý tưởng**: Mỗi đường đi từ gốc đến một nút bất kì sẽ là tiền tố của một xâu. Như vậy, việc lưu trữ các xâu có tiền tố giống nhau trở nên rất hiệu quả.

Trong **Trie**, mỗi cạnh được gán một kí tự và đường đi từ gốc tới đỉnh biểu diễn xâu được cấu tạo từ các cạnh trên đường đi đó. Ví dụ:
- Đỉnh `9`: biểu diễn xâu `bcd`
- Đỉnh `3`: biểu diễn xâu `abc`

Gọi `child(u, c)` là đỉnh con của $u$ được nối bằng cạnh có kí tự $c$, hoặc bằng $NULL$ nếu không tồn tại đỉnh con. Ta chỉ cần lưu mảng `child` với mỗi đỉnh để duy trì cấu trúc của **Trie**. Trong hình trên `child(1, 'b') = 2`, `child(5, 'b') = -1`, `child(5, 'a') = 7`.

## Cài đặt

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
```
Toàn bộ code:

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
}
```
