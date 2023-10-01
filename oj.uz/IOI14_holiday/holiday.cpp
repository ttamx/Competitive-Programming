#include"holiday.h"
#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef tuple<int,int,int,int> t4;
 
const int N=1e5+5;
const int D=250005;
const int K=1<<18;
const ll inf=1e18;
 
int n,d,st;
int a[N];
vector<pair<int,int>> vec;
int mp[N];
ll dp[4][D];
 
struct segtree{
    ll val[K];
    int freq[K];
    void update(int l,int r,int i,int x,ll v,int f){
        val[i]+=v;
        freq[i]+=f;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,v,f);
        else update(m+1,r,i*2+1,x,v,f);
    }
    void update(int x,ll v,int f){
        update(1,n,1,x,v,f);
    }
    ll query(int l,int r,int i,int k){
        if(l==r)return k>0?val[i]:0;
        int m=(l+r)/2;
        if(freq[i*2+1]<k)return query(l,m,i*2,k-freq[i*2+1])+val[i*2+1];
        return query(m+1,r,i*2+1,k);
    }
    ll query(int k){
        return query(1,n,1,k);
    }
}s;
 
void add(int i){
    s.update(mp[i],a[i],1);
}
 
void del(int i){
    s.update(mp[i],-a[i],-1);
}
 
void solver(int beg,int end,int id,int mul){
    int last=beg-1;
    queue<t4> q;
    q.emplace(1,d,beg,end);
    while(!q.empty()){
        auto [l,r,optl,optr]=q.front();
        q.pop();
        if(l>r)continue;
        int mid=(l+r)/2;
        pair<ll,int> best(0,-1);
        for(int i=optl;i<=optr;i++){
            while(last<i)add(++last);
            while(last>i)del(last--);
            best=max(best,{s.query(mid-mul*abs(i-st)),i});
        }
        int opt;
        tie(dp[id][mid],opt)=best;
        q.emplace(l,mid-1,optl,opt);
        q.emplace(mid+1,r,opt,optr);
    }
    while(last>beg-1)del(last--);
}
 
void solvel(int beg,int end,int id,int mul){
    int last=end+1;
    queue<t4> q;
    q.emplace(1,d,beg,end);
    while(!q.empty()){
        auto [l,r,optl,optr]=q.front();
        q.pop();
        if(l>r)continue;
        int mid=(l+r)/2;
        pair<ll,int> best(0,-1);
        for(int i=optr;i>=optl;i--){
            while(last>i)add(--last);
            while(last<i)del(last++);
            best=max(best,{s.query(mid-mul*abs(i-st)),i});
        }
        int opt;
        tie(dp[id][mid],opt)=best;
        q.emplace(l,mid-1,opt,optr);
        q.emplace(mid+1,r,optl,opt);
    }
    while(last<end+1)del(last++);
}
 
ll findMaxAttraction(int _n,int start,int _d,int _a[]) {
    n=_n,d=_d,st=start+1;
    for(int i=1;i<=n;i++){
        a[i]=_a[i-1];
        vec.emplace_back(a[i],i);
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<n;i++)mp[vec[i].second]=i+1;
    solver(st+1,n,0,2);
    solvel(1,st-1,1,2);
    solver(st,n,2,1);
    solvel(1,st,3,1);
    ll ans=0;
    for(int i=0;i<=d;i++){
        ans=max(ans,dp[0][i]+dp[3][d-i]);
        ans=max(ans,dp[1][i]+dp[2][d-i]);
    }
    return ans;
}