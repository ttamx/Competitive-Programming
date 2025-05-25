#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    if(k==0){
        cout << 1 << "\n";
        return;
    }
    BinaryTrie<30> t;
    int ans=n+1;
    for(int i=0,j=0;i<n;i++){
        if(!t.empty()&&t.max(a[i])>=k){
            while(!t.empty()&&t.max(a[i])>=k)t.erase(a[j++]);
            ans=min(ans,i-j+2);
        }
        t.insert(a[i]);
    }
    cout << (ans<=n?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}