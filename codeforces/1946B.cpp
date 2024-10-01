#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    ll sum=0,mn=0,mx=-LINF;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        sum+=x;
        mx=max(mx,sum-mn);
        mn=min(mn,sum);
    }
    mint ans=sum;
    if(mx>0){
        mint res=mx;
        for(int i=0;i<k;i++){
            ans+=res;
            res*=2;
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