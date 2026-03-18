#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> p(n);
    for(int i=0;i<n;i++)cin >> p[i];
    ll sum=0;
    for(int i=0;i<k;i++)sum+=n-i;
    mint ans=1;
    int cur=0;
    bool f=false;
    for(int i=0;i<n;i++){
        if(p[i]>n-k){
            if(!f)f=true;
            else ans*=(cur+1);
            cur=0;
        }else{
            cur++;
        }
    }
    cout << sum << " " << ans << "\n";
}