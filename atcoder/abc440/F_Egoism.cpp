#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

const int X=1e6+5;

void runcase(){
    int n,q;
    cin >> n >> q;
    Fenwick<int> fcnt(X);
    Fenwick<ll> fsum(X);
    multiset<int> s[2];
    ll sum=0;
    auto update=[&](int x,int v){
        fcnt.update(x,v);
        fsum.update(x,x*v);
    };
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        b[i]--;
        sum+=a[i];
        s[b[i]].emplace(a[i]);
        update(a[i],+1);
    }
    while(q--){
        int i,x,y;
        cin >> i >> x >> y;
        i--,y--;
        sum-=a[i];
        s[b[i]].extract(a[i]);
        update(a[i],-1);
        a[i]=x,b[i]=y;
        sum+=a[i];
        s[b[i]].emplace(a[i]);
        update(a[i],+1);
        if(s[1].empty()){
            cout << sum << "\n";
            continue;
        }
        int mn=*s[1].begin();
        update(mn,-1);
        int k=max(0,n-1-(int)s[1].size());
        ll ans=sum*2-mn;
        int p=fcnt.find(k);
        int c=fcnt.query(p-1);
        ans-=fsum.query(p-1)+1LL*(k-c)*p;
        update(mn,+1);
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}