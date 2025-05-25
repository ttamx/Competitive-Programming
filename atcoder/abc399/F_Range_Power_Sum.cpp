#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<mint>> coef(k+1,vector<mint>(k+1));
    for(int i=0;i<=k;i++){
        coef[i][0]=coef[i][i]=1;
        for(int j=1;j<i;j++)coef[i][j]=coef[i-1][j-1]+coef[i-1][j];
    }
    mint ans=0;
    auto rec=[&](auto &&self,int l,int r){
        if(l==r){
            mint res=1;
            for(int i=0;i<k;i++)res*=a[l];
            ans+=res;
            return;
        }
        int m=(l+r)/2;
        vector<vector<mint>> b(k+1),c(k+1);
        b[0].assign(m-l+1,mint(1));
        c[0].assign(r-m,mint(1));
        for(int i=m;i>=l;i--)b[1].emplace_back(a[i]);
        for(int i=m+1;i<=r;i++)c[1].emplace_back(a[i]);
        for(int i=1;i<b[1].size();i++)b[1][i]+=b[1][i-1];
        for(int i=1;i<c[1].size();i++)c[1][i]+=c[1][i-1];
        for(int p=2;p<=k;p++){
            b[p]=b[p-1],c[p]=c[p-1];
            for(int i=0;i<b[p].size();i++)b[p][i]*=b[1][i];
            for(int i=0;i<c[p].size();i++)c[p][i]*=c[1][i];
        }
        for(int p=0;p<=k;p++){
            mint sb=accumulate(b[p].begin(),b[p].end(),mint(0));
            mint sc=accumulate(c[k-p].begin(),c[k-p].end(),mint(0));
            ans+=coef[k][p]*sb*sc;
        }
        self(self,l,m);
        self(self,m+1,r);
    };
    rec(rec,0,n-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}