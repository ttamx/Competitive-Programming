#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=1e5+5;

int mob[N],cnt[N];
mint pw[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    mint ans=0;
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
            cnt[i]+=cnt[j];
        }
        ans+=mob[i]*(pw[cnt[i]]-1);
    }
    cout << ans;
}