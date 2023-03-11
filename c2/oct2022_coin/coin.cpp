#include "coin.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

struct segtree{
    int s[K],lz[K];
    void pushlz(int l,int r,int i){
        if(!lz[i])return;
        s[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return void(lz[i]=v),pushlz(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        s[i]=max(s[i*2],s[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

struct fenwick{
    int f[N];
    void add(int i,int v){
        while(i<N)f[i]+=v,i+=i&-i;
    }
    int read(int i){
        int ret=0;
        while(i)ret+=f[i],i-=i&-i;
        return ret;
    }
}f;

int n,l;
priority_queue<pair<int,int>> pq;

void initialize(int N,vector<int> Rail,int L){
    n=N,l=L;
    for(int i=0;i<n;i++)pq.push({Rail[i],i+1});
    return;
}

vector<int> max_dist(vector<vector<int>> coin){
    int sz=coin.size();
    map<int,vector<int>> mp;
    for(int i=0;i<sz;i++)mp[coin[i][2]].push_back(i);
    vector<int> ans(sz);
    auto it=mp.end();
    do{
        it--;
        while(!pq.empty()&&pq.top().first>it->first){
            int i=pq.top().second;
            pq.pop();
            f.add(i,1);
            s.update(1,n,1,max(1,i-l+1),i,1);
        }
        for(auto i:it->second){
            int a=coin[i][0]+1;
            int b=coin[i][1];
            int l=a-1,r=n;
            int st=f.read(a-1);
            while(l<r){
                int m=(l+r+1)/2;
                if(f.read(m)-st>b)r=m-1;
                else l=m;
            }
            int hop=s.query(1,n,1,a,l+1);
            r=n;
            while(l<r){
                int m=(l+r+1)/2;
                if(f.read(m)-st>b+hop)r=m-1;
                else l=m;
            }
            ans[i]=l;
        }
    }while(it!=mp.begin());
    return ans;
}
