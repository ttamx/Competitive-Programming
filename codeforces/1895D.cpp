#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=1;i<n;i++){
        cin >> a[i];
        a[i]^=a[i-1];
    }
    BinaryTrie<20> tr;
    for(auto x:a){
        tr.insert(x);
    }
    for(int i=0;i<n;i++){
        if(tr.max(i)==n-1){
            for(auto x:a){
                cout << (x^i) << " ";
            }
            cout << "\n";
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}