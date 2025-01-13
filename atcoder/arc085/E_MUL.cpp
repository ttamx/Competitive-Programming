#include "template.hpp"
#include "flow/dinic.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    ll base=0;
    int s=0,t=n+1;
    Dinic<ll> mf(n+2,s,t);
    for(int i=1;i<=n;i++){
        if(a[i]>0){
            base+=a[i];
            mf.add_edge(i,t,a[i]);
        }else{
            mf.add_edge(s,i,-a[i]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i*2;j<=n;j+=i){
            mf.add_edge(i,j,(ll)1e12);
        }
    }
    cout << base-mf.flow();
}