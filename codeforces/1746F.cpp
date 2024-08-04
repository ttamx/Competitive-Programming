#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<tuple<int,int,int,int>> qr(q);
    auto vals=a;
    for(auto &[t,l,r,x]:qr){
        cin >> t;
        if(t==1){
            cin >> l >> x;
            l--;
            vals.emplace_back(x);
        }else{
            cin >> l >> r >> x;
            l--,r--;
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int m=vals.size();
    for(auto &x:a)x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
    for(auto &[t,l,r,x]:qr)if(t==1)x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
    vector mask(30,vector<int>(m));
    for(auto &v:mask)for(auto &x:v)x=rng()&1;
    vector<Fenwick<int>> f(30,n);
    auto update=[&](int i,int v){
        for(int j=0;j<30;j++){
            if(mask[j][a[i]]){
                f[j].update(i,v);
            }
        }
    };
    for(int i=0;i<n;i++)update(i,1);
    for(auto &[t,l,r,x]:qr){
        cin >> t;
        if(t==1){
            update(l,-1);
            a[l]=x;
            update(l,1);
        }else{
            if(x==1){
                cout << "YES\n";
            }else{
                bool ok=true;
                for(int i=0;i<30;i++){
                    if(f[i].query(l,r)%x!=0){
                        ok=false;
                        break;
                    }
                }
                cout << (ok?"YES":"NO") << "\n";
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}