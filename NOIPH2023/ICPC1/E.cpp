#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,l,h;
int ans;
int p[N];
vector<pair<int,int>> vec;
multiset<pair<int,int>> ms;
deque<int> dq;

int fp(int u){
    if(p[u]==u)return u;
    return p[u]=fp(p[u]);
}

void unite(int u,int v){
    u=fp(u),v=fp(v);
    if(u==v)return;
    p[u]=v;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> l >> h;
    iota(p,p+n,0);
    vec.resize(n);
    for(auto &[x,y]:vec)cin >> x >> y;
    sort(vec.begin(),vec.end());
    for(int i=0;i<n;i++){
        auto [x,y]=vec[i];
        while(!dq.empty()&&vec[dq.front()].first+l<x){
            ms.erase(ms.find(make_pair(vec[dq.front()].second,dq.front())));
            dq.pop_front();
        }
        auto l=ms.lower_bound(make_pair(y-h,0)),r=ms.lower_bound(make_pair(y+h+1,0));
        if(l!=ms.end()&&l->first<=y+h){
            unite(i,l->second);
        }
        if(r!=ms.begin()&&(--r)->first+h>=y){
            unite(i,r->second);
        }
        ms.emplace(y,i);
        dq.emplace_back(i);
    }
    for(int i=0;i<n;i++)if(fp(i)==i)ans++;
    cout << ans;
}