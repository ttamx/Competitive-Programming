#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int l,r;
    cin >> l >> r;
    BinaryTrie<17> trie;
    vector<int> a;
    for(int i=l;i<=r;i++){
        int x;
        cin >> x;
        trie.insert(x);
        a.emplace_back(x^l);
    }
    for(auto x:a){
        if(trie.min(x)==l&&trie.max(x)==r){
            cout << x << "\n";
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}