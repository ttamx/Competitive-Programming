#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;
const int K=1<<20;

int n,m,q;
int a[N];
int cnt[N];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> qr;
int ans[N];
vector<int> vec[N];

struct segtree{
    int t[K];
    void update(int l,int r,int i,int x,int v){
        if(r<x||x<l)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int v){
        update(1,m,1,x,v);
    }
    int query(int l,int r,int i,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        if(k<=t[i*2])return query(l,m,i*2,k);
        else return query(m+1,r,i*2+1,k-t[i*2]);
    }
    int query(int k){
        return query(1,m,1,k);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        a[x]++;
    }
    for(int i=1;i<=q;i++){
        ll x;
        cin >> x;
        qr.emplace(x-n,i);
    }
    for(int i=1;i<=m;i++){
        cnt[a[i]]++;
        vec[a[i]].emplace_back(i);
    }
    ll cur=0,freq=0;
    for(int i=0;i<=n;i++){
        while(!qr.empty()&&qr.top().first<=cur+freq){
            auto [val,id]=qr.top();
            qr.pop();
            ans[id]=s.query((val-cur-1)%freq+1);
        }
        cur+=freq;
        freq+=cnt[i];
        for(auto x:vec[i])s.update(x,1);    }
    while(!qr.empty()){
        auto [val,id]=qr.top();
        qr.pop();
        ans[id]=s.query((val-cur-1)%freq+1);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}