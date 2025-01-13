#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=5e5+5;

int mob[N],cnt[N];
vector<int> divisors[N];

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    mint ans=0;
    for(int i=1;i<=m;i++){
        for(int d:divisors[i]){
            cnt[d]++;
        }
    }
    for(int k=1;k<=m;k++){
        for(int g:divisors[k]){
            mint cur=0;
            for(int d:divisors[k/g]){
                cur+=mob[d]*cnt[d*g];
            }
            ans+=binpow(cur,n);
        }
    }
    cout << ans << "\n";
    for(int i=1;i<=m;i++){
        for(int d:divisors[i]){
            cnt[d]--;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
    }
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}