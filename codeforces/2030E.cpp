#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=200'005;
const mint ZERO=mint(0);

mint fac[N],ifac[N],pw[N];

mint C(int n,int r){
    if(n<0||r<0||n<r)return ZERO;
    return fac[n]*ifac[n-r]*ifac[r];
}

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
    vector<mint> ways(n+1);
    int sz=cnt[0];
    int rem=n-cnt[0];
    for(int i=1;i<=sz;i++){
        ways[i]=C(cnt[0],i);
        ans+=ways[i]*pw[rem]*i;
    }
    int timer=0;
    for(int i=1;i<n;i++){
        if(cnt[i]==0)break;
        rem-=cnt[i];
        vector<mint> nways(sz+1);
        mint tmp=0;
        timer+=cnt[i];
        assert(timer<=4*n);
        for(int j=cnt[i];j>=1;j--){
            if(j<=sz)nways[j]+=tmp*ways[j];
            tmp+=C(cnt[i],j);
        }
        tmp=0;
        timer+=sz;
        assert(timer<=4*n);
        for(int j=sz;j>=1;j--){
            tmp+=ways[j];
            nways[j]+=tmp*C(cnt[i],j);
        }
        swap(ways,nways);
        sz=min(sz,cnt[i]);
        for(int j=1;j<=sz;j++){
            ans+=ways[j]*pw[rem]*j;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<=N-1;i++)fac[i]=fac[i-1]*i;
    ifac[N-1]=fac[N-1].inv();
    for(int i=N-1;i>=1;i--)ifac[i-1]=ifac[i]*i;
    pw[0]=1;
    for(int i=1;i<=N-1;i++)pw[i]=pw[i-1]*2;
    int t(1);
    cin >> t;
    while(t--)runcase();
}