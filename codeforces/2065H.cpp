#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    vector<Fenwick<mint>> fl(2,Fenwick<mint>(n)),fr(2,Fenwick<mint>(n));
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    mint ans=pw[n]-1;
    vector<int> a(n);
    auto toggle=[&](int i){
        if(i>0){
            ans-=fl[a[i]^1].query(0,i-1)*pw[n-i-1];
        }
        if(i<n-1){
            ans-=fr[a[i]^1].query(i+1,n-1)*pw[i];
        }
        fl[a[i]].update(i,-pw[i]);
        fr[a[i]].update(i,-pw[n-i-1]);
        a[i]^=1;
        fl[a[i]].update(i,pw[i]);
        fr[a[i]].update(i,pw[n-i-1]);
        if(i>0){
            ans+=fl[a[i]^1].query(0,i-1)*pw[n-i-1];
        }
        if(i<n-1){
            ans+=fr[a[i]^1].query(i+1,n-1)*pw[i];
        }
    };
    for(int i=0;i<n;i++){
        fl[0].update(i,pw[i]);
        fr[0].update(i,pw[n-i-1]);
    }
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            toggle(i);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        toggle(x-1);
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