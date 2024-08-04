#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto calc=[&](int x){
        BinaryTrie<30> t;
        ll res=0;
        int l=0,r=0;
        for(;r<n;r++){
            while(t.size()>0&&t.min(a[r])<=x){
                t.erase(a[l]);
                l++;
            }
            res+=l;
            t.insert(a[r]);
        }
        return res;
    };
    ll l=0,r=(1<<30)-1;
    while(l<r){
        ll m=(l+r)/2;
        if(calc(m)>=k)r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}