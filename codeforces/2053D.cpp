#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    auto c=a,d=b;
    sort(c.begin(),c.end());
    sort(d.begin(),d.end());
    mint ans=1;
    for(int i=0;i<n;i++){
        ans*=min(c[i],d[i]);
    }
    cout << ans << " ";
    while(q--){
        int o,x;
        cin >> o >> x;
        x--;
        if(o==1){
            int i=upper_bound(c.begin(),c.end(),a[x])-c.begin()-1;
            ans/=min(c[i],d[i]);
            c[i]++;
            a[x]++;
            ans*=min(c[i],d[i]);
        }else{
            int i=upper_bound(d.begin(),d.end(),b[x])-d.begin()-1;
            ans/=min(c[i],d[i]);
            d[i]++;
            b[x]++;
            ans*=min(c[i],d[i]);
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}