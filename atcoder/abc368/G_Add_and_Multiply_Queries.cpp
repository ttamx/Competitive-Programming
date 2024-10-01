#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    Fenwick<ll> f(a);
    set<int> pos;
    for(int i=0;i<n;i++){
        if(b[i]>1){
            pos.emplace(i);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int x,v;
            cin >> x >> v;
            x--;
            f.update(x,v-a[x]);
            a[x]=v;
        }else if(op==2){
            int x,v;
            cin >> x >> v;
            x--;
            pos.erase(x);
            b[x]=v;
            if(b[x]>1){
                pos.emplace(x);
            }
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            ll v=a[l];
            int p=l;
            for(auto it=pos.upper_bound(l);it!=pos.end()&&*it<=r;it++){
                int x=*it;
                v+=f.query(p+1,x-1);
                v=max(v+a[x],v*b[x]);
                p=x;
            }
            v+=f.query(p+1,r);
            cout << v << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}