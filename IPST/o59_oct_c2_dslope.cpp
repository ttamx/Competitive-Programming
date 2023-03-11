#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=8e4+5;
const int K=45;
const int MOD=1e9-1;

int n,k;
ll a[N];

struct fenwick{
    ll tree[N];
    void add(int i,ll v){for(;i<=n;i+=i&-i)tree[i]=(tree[i]+v)%MOD;}
    ll read(int i){ll ret=0;for(;i>0;i-=i&-i)ret=(ret+tree[i])%MOD;return ret;}
}fw[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i)cin >> a[i];
    for(int i=1;i<=n;++i){
        fw[1].add(a[i],1);
        for(int j=2;j<=k;++j){
            ll cnt=(fw[j-1].read(n)-fw[j-1].read(a[i])+MOD)%MOD;
            fw[j].add(a[i],cnt);
        }
    }
    cout << fw[k].read(n);
}
