#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

void runcase(){
    ll n,m,q;
    cin >> n >> m >> q;
    auto is_border=[&](int i,int j){
        if(1<i&&i<n&&1<j&&j<m)return false;
        if((i==1||i==n)&&(j==1||j==m))return false;
        return true;
    };
    int s=0;
    ll inner=(n-2)*(m-2)+4;
    ll border=n*m-inner;
    while(q--){
        int x,y,c;
        cin >> x >> y >> c;
        if(is_border(x,y)){
            s^=c;
            border--;
        }else{
            inner--;
        }
    }
    if(s&&border==0){
        cout << 0 << "\n";
    }else{
        cout << binpow(mint(2),inner+max(border-1,0LL)) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}