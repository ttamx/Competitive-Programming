#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    n=a.size();
    int m=a.back();
    vector<bool> f(m+2);
    vector<int> nxt(m+1,m+1);
    for(auto i:a)nxt[i]=i;
    for(int i=m-1;i>=1;i--)nxt[i]=min(nxt[i],nxt[i+1]);
    a.pop_back();
    vector<tuple<int,int,int>> e;
    auto push=[&](int x,int y){e.emplace_back(y%x,x,y);};
    for(auto i:a){
        push(i,nxt[i+1]);
        for(int j=i*2;j<=m;j+=i)push(i,nxt[j]);
    }
    ll ans=0;
    DSU dsu(m+1);
    sort(e.begin(),e.end());
    for(auto [w,u,v]:e)if(dsu.merge(u,v))ans+=w;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}