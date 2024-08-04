#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=5005;

mint C[N][N];

void runcase(){
    int n;
    cin >> n;
    mint ans=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=2*i+1&&j<=n;j++){
            ans+=j*C[j-1][j-i-1]*C[n-j][2*i-j+1];
        }
        if(2*i+1>n){
            ans+=C[n][i]*(i*2+1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}