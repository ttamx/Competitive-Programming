#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=5005;
const mint ZERO=mint(0);

mint fac[N],ifac[N],pw[N];

mint C(int n,int r){
    if(n<0||r<0||n<r)return ZERO;
    return fac[n]*ifac[n-r]*ifac[r];
}

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> l(n),r(n);
    vector<pair<pair<int,int>,int>> a;
    for(int i=0;i<n;i++){
        cin >> l[i].first >> r[i].first;
        l[i].second=i*2;
        r[i].second=i*2+1;
        a.emplace_back(l[i],i);
        a.emplace_back(r[i],i);
    }
    sort(a.begin(),a.end());
    mint ans=0;
    for(auto [cur,t]:a){
        int cntl=0,cntr=0;
        for(int i=0;i<n;i++){
            if(i==t)continue;
            if(r[i]<cur){
                cntl++;
            }
            if(l[i]>cur){
                cntr++;
            }
        }
        int rem=n-cntl-cntr-1;
        mint wayl=0,wayr=0;
        if(cur.second%2){
            for(int i=0;i<cntl;i++){
                wayl+=C(cntl-1,i)*C(cntr,i+2);
            }
            for(int i=0;i<cntr;i++){
                wayr+=C(cntr-1,i)*C(cntl,i);
            }
        }else{
            for(int i=0;i<cntl;i++){
                wayl+=C(cntl-1,i)*C(cntr,i+1);
            }
            for(int i=0;i<cntr;i++){
                wayr+=C(cntr-1,i)*C(cntl,i+1);
            }
        }
        mint res=0;
        for(int i=0;i<n;i++){
            if(i==t)continue;
            if(r[i]<cur){
                res+=(cur.first-r[i].first)*wayl;
            }
            if(l[i]>cur){
                res+=(l[i].first-cur.first)*wayr;
            }
        }
        ans+=res*pw[rem];
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