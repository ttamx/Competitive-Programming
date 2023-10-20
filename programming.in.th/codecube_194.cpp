#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N],mp[N];
vector<pair<int,long long>> v;

struct fenwick{
    pair<int,long long> t[N];
    void upd(int i,pair<int,long long> v){
        for(;i<N;i+=i&-i)t[i]=max(t[i],v);
    }
    pair<int,long long> get(int i){
        pair<int,long long> res={0,0};
        for(;i>0;i-=i&-i)res=max(res,t[i]);
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    iota(mp,mp+n+1,0);
    for(int i=1;i<=n;i++)cin >> a[i],v.emplace_back(a[i],i);
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)mp[v[i].second]=i+1;
    for(int i=1;i<=n;i++){
        auto [x,y]=f.get(mp[i]);
        f.upd(mp[i],{x+1,y+a[i]});
    }
    auto [x,y]=f.get(n);
    cout << x << ' ' << y;
}