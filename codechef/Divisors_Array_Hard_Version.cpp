#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

const int N=1e7+5;

int lp[N];
int cnt[N];
mint ans=1;

void update(int i,int v){
    ans*=comb.inv(cnt[i]+1);
    cnt[i]+=v;
    ans*=cnt[i]+1;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        for(int x=i;x>1;x/=lp[x]){
            update(lp[x],+1);
        }
    }
    for(int i=0;i<n;i++){
        int val;
        cin >> val;
        int x=val;
        for(int x=val;x>1;x/=lp[x]){
            update(lp[x],+1);
        }
        cout << ans << " ";
        for(int x=val;x>1;x/=lp[x]){
            update(lp[x],-1);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i]==0){
            for(int j=i;j<N;j+=i){
                if(lp[j]==0){
                    lp[j]=i;
                }
            }
        }
    }
    int t(1);
    while(t--)runcase();
}