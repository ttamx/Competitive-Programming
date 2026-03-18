#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    string s,t;
    cin >> s >> t;
    for(int i=0;i<n;i+=2){
        if(s[i]!='?'){
            s[i]^=1;
        }
    }
    for(int i=0;i<n;i+=2){
        if(t[i]!='?'){
            t[i]^=1;
        }
    }
    s=" "+s;
    t=" "+t;
    vector<vector<mint>> pre(n+2,vector<mint>(n*2+1)),suf(n+2,vector<mint>(n*2+1));
    pre[0][n]=suf[n+1][n]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<2*n;j++){
            for(int x=0;x<2;x++){
                if(s[i]!='?'&&s[i]!='0'+x)continue;
                for(int y=0;y<2;y++){
                    if(t[i]!='?'&&t[i]!='0'+y)continue;
                    pre[i][j+x-y]+=pre[i-1][j];
                }
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<2*n;j++){
            for(int x=0;x<2;x++){
                if(s[i]!='?'&&s[i]!='0'+x)continue;
                for(int y=0;y<2;y++){
                    if(t[i]!='?'&&t[i]!='0'+y)continue;
                    suf[i][j+x-y]+=suf[i+1][j];
                }
            }
        }
    }
    mint ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=2*n;j++){
            ans+=pre[i][j]*suf[i+1][2*n-j]*abs(j-n);
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