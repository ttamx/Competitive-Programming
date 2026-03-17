#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    ll sum=0;
    for(auto &x:a){
        cin >> x;
        sum^=x;
    }
    ll cur=0;
    ll ans=0;
    BinaryTrie<60,int64_t> t;
    t.insert(0);
    for(auto x:a){
        cur^=x;
        sum^=x;
        t.insert(cur);
        ans=max(ans,cur);
        ans=max(ans,t.max(sum));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}