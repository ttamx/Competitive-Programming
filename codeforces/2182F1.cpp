#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> cnt(61);
    vector<mint> pw(n+m+1);
    pw[0]=1;
    for(int i=1;i<=n+m;i++)pw[i]=pw[i-1]*2;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    while(m--){
        ll op,x;
        cin >> op >> x;
        if(op==1){
            cnt[x]++;
            n++;
        }else if(op==2){
            cnt[x]--;
            n--;
        }else{
            x--;
            mint ans=0,base=1;
            int c=0,p=60,rem=n;
            for(int i=60;i>=0;i--){
                if(x>>i&1){
                    c++;
                    continue;
                }
                if(cnt[p]<c)break;
                rem-=cnt[p];
                mint ways=pw[cnt[p]];
                for(int i=0;i<=c;i++){
                    ways-=comb.C(cnt[p],i);
                }
                ans+=base*ways*pw[rem];
                base*=comb.C(cnt[p],c);
                c=0;
                p--;
            }
            cout << ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}