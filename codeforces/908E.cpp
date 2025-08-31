#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=1005;

mint C[N][N],b[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,n;
    cin >> m >> n;
    vector<ll> a(m);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            if(s[j]=='1'){
                a[j]|=1LL<<i;
            }
        }
    }
    for(int i=0;i<=m;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    b[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=i;j++){
            b[i]+=b[i-j]*C[i-1][j-1];
        }
    }
    mint ans=1;
    sort(a.begin(),a.end());
    for(int i=0;i<m;){
        int j=i+1;
        while(j<m&&a[i]==a[j]){
            j++;
        }
        ans*=b[j-i];
        i=j;
    }
    cout << ans << "\n";
}