#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=1e6+5;
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
    vector<pair<int,int>> ls,rs;
    for(int i=0;i<n;i++){
        cin >> l[i].first >> r[i].first;
        l[i].second=i*2;
        r[i].second=i*2+1;
        a.emplace_back(l[i],i);
        a.emplace_back(r[i],i);
        ls.emplace_back(l[i]);
        rs.emplace_back(r[i]);
    }
    sort(a.begin(),a.end());
    sort(ls.rbegin(),ls.rend());
    sort(rs.rbegin(),rs.rend());
    mint ans=0;
    int cntl=0,cntr=0;
    mint suml=0,sumr=0;
    for(auto [val,_]:ls){
        sumr+=val;
        cntr++;
    }
    for(auto [cur,t]:a){
        while(!rs.empty()&&rs.back()<cur){
            suml+=rs.back().first;
            cntl++;
            rs.pop_back();
        }
        while(!ls.empty()&&ls.back()<=cur){
            sumr-=ls.back().first;
            cntr--;
            ls.pop_back();
        }
        int rem=n-cntl-cntr-1;
        mint wayl=0,wayr=0;
        if(cur.second%2){
            if(cntl>=1&&cntr>=2){
                wayl=C(cntl+cntr-1,cntl+1);
            }
            if(cntr>=1){
                wayr=C(cntl+cntr-1,cntl);
            }
        }else{
            if(cntl>=1&&cntr>=1){
                wayl=C(cntl+cntr-1,cntl);
            }
            if(cntl>=1&&cntr>=1){
                wayr=C(cntl+cntr-1,cntr);
            }
        }
        mint res=0;
        mint val=cur.first;
        res+=(val*cntl-suml)*wayl;
        res+=(sumr-val*cntr)*wayr;
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