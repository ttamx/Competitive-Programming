#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=0){
            continue;
        }
        if(a[a[i]]==-1){
            a[a[i]]=i;
        }
        if(a[a[i]]!=i){
            cout << 0 << "\n";
            return;
        }
    }
    int cnt=0;
    for(int i=1;i<n;i++){
        if(a[i]==-1){
            cnt++;
        }
    }
    vector<mint> pw(n+2);
    pw[0]=1;
    for(int i=1;i<=n+1;i++){
        pw[i]=pw[i-1]*2;
    }
    mint ans=0;
    if(a[n]!=-1){
        mint ways=1;
        for(int i=cnt;i>=0;i-=2){
            ans+=ways*pw[i];
            ways*=comb.C(i,2);
        }
    }else{
        {
            mint ways=1;
            for(int i=cnt;i>=0;i-=2){
                ans+=ways*pw[i];
                ways*=comb.C(i,2);
            }
        }
        {
            mint ways=cnt;
            for(int i=cnt-1;i>=0;i-=2){
                ans+=ways*pw[i];
                ways*=comb.C(i,2);
            }
        }
    }
    cout << ans << "\n";
}

const int n=4;
int tot;
int a[n+1],b[n+1];

void solve(int i){
    if(i>n){
        for(int i=0;i<=n;i++){
            b[i]=0;
        }
        for(int i=0;i<=n;i++){
            b[a[i]]+=i;
        }
        bool ok=true;
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]){
                ok=false;
            }
        }
        if(ok&&a[n]>0){
            for(int i=1;i<=n;i++){
                cout << a[i] << " \n"[i==n];
            }
            tot++;
        }
        return;
    }
    for(int v=0;v<=n;v++){
        a[i]=v;
        solve(i+1);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    solve(1);
    cout << tot << "\n";
    // int t(1);
    // cin >> t;
    // while(t--)runcase();
}