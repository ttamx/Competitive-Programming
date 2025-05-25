#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=1000005;

int cnt[N],mob[N];
mint pw[N];

void runcase(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            cnt[i]+=cnt[j];
            mob[j]-=mob[i];
        }
    }
    int ans=0;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    for(int i=1;i<N;i++){
        mint res=0;
        for(int j=i,k=1;j<N;j+=i,k++){
            res+=mob[k]*(pw[cnt[j]]-1);
        }
        if(res.val()>0)ans++;
    }
    cout << ans-n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}