#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<mint> hsh(26),pw1(n+1),pw2(m+1);
    for(auto &x:hsh)x=rng();
    int ans=n*m*4;
    for(int t=0;t<2;t++){
        mint base=rng();
        pw1[0]=1;
        for(int i=1;i<pw1.size();i++){
            pw1[i]=pw1[i-1]*base;
        }
        swap(pw1,pw2);
    }
    for(int t=0;t<4;t++){
        vector<vector<mint>> f1(n+1,vector<mint>(m+1));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f1[i][j]=f1[i][j-1]+f1[i-1][j]-f1[i-1][j-1]+hsh[a[i-1][j-1]-'a']*pw1[i]*pw2[j];
            }
        }
        vector<vector<mint>> f2(n+1,vector<mint>(m+1));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f2[i][j]=f2[i][j-1]+f2[i-1][j]-f2[i-1][j-1]+hsh[a[n-i][m-j]-'a']*pw1[i]*pw2[j];
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(f1[i][j]*pw1[n-i]*pw2[m-j]==f2[n][m]-f2[n][m-j]-f2[n-i][m]+f2[n-i][m-j]){
                    ans=min(ans,(n*2-i)*(m*2-j));
                }
            }
        }
        reverse(a.begin(),a.end());
        if(t==1){
            for(auto &x:a){
                reverse(x.begin(),x.end());
            }
        }
    }
    cout << ans-n*m << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}