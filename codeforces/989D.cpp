#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,w,l;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(i++;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> l >> w;
    vector<pair<int,int>> a(n);
    for(auto &[x,v]:a){
        cin >> x >> v;
    }
    long long ans=0;
    sort(a.begin(),a.end());
    vector<int> b,c;
    for(auto [x,v]:a){
        (v==1?b:c).emplace_back(x);
    }
    int p=0;
    for(auto x:b){
        while(p<c.size()&&(c[p]<x||1LL*w*(c[p]-x+l)<=abs(c[p]+x+l))){
            p++;
        }
        ans+=c.size()-p;
    }
    cout << ans << "\n";
}