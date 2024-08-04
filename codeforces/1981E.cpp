#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<tuple<int,int,int>> v;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r >> a[i];
        v.emplace_back(l,0,i);
        v.emplace_back(r,1,i);
    }
    sort(v.begin(),v.end());
    multiset<pair<int,int>> ms;
    vector<tuple<int,int,int>> e;
    for(auto [p,t,i]:v){
        if(t==0){
            if(!ms.empty()){
                auto it=ms.lower_bound(make_pair(a[i],0));
                if(it!=ms.end()){
                    auto [y,j]=*it;
                    e.emplace_back(y-a[i],i,j);
                }
                if(it!=ms.begin()){
                    auto [y,j]=*prev(it);
                    e.emplace_back(a[i]-y,i,j);
                }
            }
            ms.emplace(a[i],i);
        }else{
            ms.erase(ms.find(make_pair(a[i],i)));
        }
    }
    sort(e.begin(),e.end());
    DSU dsu(n);
    ll ans=0;
    for(auto [w,u,v]:e){
        if(dsu.merge(u,v)){
            ans+=w;
        }
    }
    if(dsu.size(0)<n){
        cout << -1 << "\n";
    }else{
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}