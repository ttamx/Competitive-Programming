#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> cnt(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    mint ans=0;
    auto mn=cnt;
    for(int i=2;i<n;i++)mn[i]=min(mn[i],mn[i-1]);
    auto f=cnt;
    for(int i=n-2;i>=0;i--)f[i]+=f[i+1];
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    vector<mint> g(n);
    for(int i=0;i<n;i++)g[i]=pw[cnt[i]];
    for(int v=1;v<=n;v++){
        mint ways=1;
        for(int i=1;i<n&&cnt[i]>=v;i++){
            g[i]-=comb.C(cnt[i],v-1);
            ways*=g[i];
            ans+=ways*pw[(i+v+1<n)?f[i+v+1]:0];
        }
    }
    for(int i=2;i<n;i++){
        ans+=pw[f[i]]-1;
    }
    ans*=(pw[cnt[0]]-1);
    for(int i=1;i<n;i++){
        ans+=pw[f[i]]-1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}