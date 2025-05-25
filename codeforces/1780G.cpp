#include "template.hpp"
#include "string/suffix-array.hpp"
#include "data-structure/dsu.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    SuffixArray sa(s);
    vector<vector<int>> event(n+1);
    for(int i=2;i<=n;i++){
        event[sa.lcp[i]].emplace_back(i-1);
    }
    ll ans=0;
    DSU dsu(n);
    vector<int> cnt(n+1);
    cnt[1]=n;
    for(int i=n;i>=1;i--){
        for(auto j:event[i]){
            cnt[dsu.size(j-1)]--;
            cnt[dsu.size(j)]--;
            dsu.merge(j-1,j);
            cnt[dsu.size(j)]++;
        }
        for(int j=i;j<=n;j+=i){
            ans+=1LL*cnt[j]*j;
        }
    }
    cout << ans;
}