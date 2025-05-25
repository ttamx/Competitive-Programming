#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),pos(n,-1);
    vector<bool> bad(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        if(a[i]!=-1){
            bad[a[i]]=true;
            pos[a[i]]=i;
        }
    }
    vector<int> c(n+1);
    for(int i=0;i<n;i++)c[i+1]=c[i]+(a[i]==-1);
    int cc=c[n];
    vector<int> f(n+1);
    mint ans=0;
    vector<vector<mint>> v(n+1,vector<mint>(n+1));
    for(int i=0;i<=cc;i++){
        v[i][0]=0;
        for(int j=1;j<=i;j++){
            v[i][j]=v[i][j-1]+comb.P(i,j)*comb.fac(cc-j);
        }
    }
    for(int l=0;l<n;l++){
        int cnt=0,lim=0,cv=0;
        auto b=bad;
        for(int r=l;r<n;r++){
            if(a[r]==-1)cnt++;
            else b[a[r]]=false;
            while(lim<n&&!b[lim]){
                if(bad[lim])cv++;
                lim++;
            }
            ans+=v[cnt][min(lim-cv,cnt)];
        }
    }
    int id=0;
    while(id<n&&pos[id]==-1)id++;
    if(id<n){
        for(int l=pos[id];l>=0;l--)for(int r=pos[id];r<n;r++)f[c[r+1]-c[l]]++;
        int last=-1,gap=0;
        int l=pos[id],r=pos[id];
        for(;id<n;id++){
            if(pos[id]==-1)continue;
            for(;pos[id]>r;r++)for(int j=0;j<=l;j++)f[c[r+1]-c[j]]--;
            for(;pos[id]<l;l--)for(int j=r;j<n;j++)f[c[j+1]-c[l]]--;
            gap+=id-last-1;
            for(int cnt=gap;cnt<=cc;cnt++){
                ans+=f[cnt]*comb.P(cnt,gap)*comb.fac(cc-gap);
            }
            last=id;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}