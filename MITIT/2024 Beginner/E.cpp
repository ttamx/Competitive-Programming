#include "template.hpp"
#include "data-structure/binary-trie.hpp"

const int N=1e5+5;

int n,k;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    ll ans=0;
    {
        BinaryTrie<30> t;
        for(int l=1,r=1;r<=n;r++){
            while(!t.empty()&&t.min(a[r])<k){
                t.erase(a[l]);
                l++;
            }
            ans+=r-l+1;
            t.insert(a[r]);
        }
    }
    {
        BinaryTrie<30> t;
        for(int l=1,r=1;r<=n;r++){
            while(!t.empty()&&t.min(a[r])<=k){
                t.erase(a[l]);
                l++;
            }
            ans-=r-l+1;
            t.insert(a[r]);
        }
    }
    cout << ans << "\n";
}