#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;
const ll INF=1e18;
const int INF2=2e9;

int n,k;
vector<tuple<int,int,int>> a,b;

struct Segtree{
    pair<int,int> t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]={INF2,l});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void modify(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i].first=v);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {INF2,-1};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

vector<ll> calc(vector<tuple<int,int,int>> &a){
    int n=0;
    vector<pair<int,int>> cc;
    for(auto [_,t,v]:a){
        if(t)cc.emplace_back(v,n++);
    }
    if(!n)return {0};
    sort(cc.begin(),cc.end());
    vector<int> ord(n);
    for(int i=0;i<n;i++){
        ord[cc[i].second]=i;
    }
    seg.build(0,n-1,1);
    int p=0;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(auto [_,t,v]:a){
        if(t){
            int cost=INF2;
            if(!pq.empty()){
                cost=pq.top();
                pq.pop();
            }
            int idx=ord[p++];
            while(true){
                auto [v,i]=seg.query(0,n-1,1,idx+1,n-1);
                if(v>=cost)break;
                seg.modify(0,n-1,1,idx,v);
                idx=i;
            }
            seg.modify(0,n-1,1,idx,cost);
        }else{
            pq.emplace(v);
        }
    }
    vector<ll> c{0};
    while(true){
        auto [x,y]=seg.query(0,n-1,1,0,n-1);
        if(x==INF2)break;
        c.emplace_back(x+cc[y].first);
        seg.modify(0,n-1,1,y,INF2);
    }
    sort(c.begin(),c.end());
    for(int i=1;i<c.size();i++){
        c[i]+=c[i-1];
    }
    if(c.size()>k+1)c.resize(k+1);
    return c;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++){
        int t,x,y,c;
        cin >> t >> x >> y >> c;
        if(t<=2){
            a.emplace_back(x,t%2,c);
        }else{
            b.emplace_back(y,t%2,c);
        }
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    auto aa=calc(a);
    auto bb=calc(b);
    ll ans=INF;
    for(int i=0;i<aa.size();i++){
        if(k-i<bb.size()){
            ans=min(ans,aa[i]+bb[k-i]);
        }
    }
    cout << (ans<INF?ans:-1LL) << "\n";
}