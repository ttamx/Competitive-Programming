#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    vector<int> b;
    for(auto &[x,y]:a){
        cin >> x >> y;
        b.emplace_back(x);
        b.emplace_back(y);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    n=b.size();
    vector<int> fa(n),mx(n),mx2(n),cnt(n);
    for(int i=0;i<n;i++){
        fa[i]=i;
        mx[i]=i;
        mx2[i]=0;
    }
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    for(auto &[x,y]:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin();
        y=lower_bound(b.begin(),b.end(),y)-b.begin();
    }
    for(auto [u,v]:a){
        u=fp(u),v=fp(v);
        if(u==v){
            if(++cnt[u]>1){
                cout << -1 << "\n";
                exit(0);
            }
        }else{
            mx2[u]=max(mx2[u],mx[v]);
            if(mx2[u]>mx[u])swap(mx[u],mx2[u]);
            mx2[u]=max(mx2[u],mx2[v]);
            if(mx2[u]>mx[u])swap(mx[u],mx2[u]);
            cnt[u]+=cnt[v];
            fa[v]=u;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(i==fp(i)){
            ans=max(ans,cnt[i]?mx[i]:mx2[i]);
        }
    }
    cout << b[ans] << "\n";
}