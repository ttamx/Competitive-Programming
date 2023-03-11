#include "coin.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n,l;
int qs[N],cnt[N],cover[N];
vector<int> v,nv;
priority_queue<pair<int,int>> pq;
map<int,vector<int>> mp;

struct fenwick{
    int f[N];
    void add(int i,int v){
        while(i<N){
            f[i]+=v;
            i+=i&-i;
        }
    }
    int read(int i){
        int ret=0;
        while(i){
            ret+=f[i];
            i-=i&-i;
        }
        return ret;
    }
}f;

struct segtree{
    int tree[K];
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r){
            tree[i]=v;
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        tree[i]=max(tree[i*2],tree[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(l>y||r<x)return 0;
        if(x<=l&&r<=y)return tree[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

void initialize(int N,std::vector<int> Rail,int L)
{
	n=N;
	l=L;
	v.resize(n+1);
    for(int i=1;i<=n;i++){
        v[i]=Rail[i-1];
        pq.push({v[i],i});
        qs[i]=qs[i-1]+v[i];
        if(v[i]<=l){
            cnt[i]++;
        }
    }
    int idx=n;
    while(idx>=1){
        if(cnt[idx]){
            int tmp=idx;
            while(cnt[idx]){
                cover[idx]=tmp;
                idx--;
            }
        }else{
            idx--;
        }
    }
    return;
}

std::vector<int> max_dist(std::vector<std::vector<int> > q)
{
    std::vector<int> Ans(q.size());
    for(int i=0;i<q.size();i++){
        int sz=q[i][2];
        mp[sz].push_back(i);
    }
    auto it=mp.end();
    do{
        it--;
        auto [sz,v]=*it;
        queue<int> tmp;
        while(!pq.empty()&&pq.top().first>sz){
            int i=pq.top().second;
            f.add(i,1);
            tmp.push(i);
            pq.pop();
        }
        while(!tmp.empty()){
            int i=tmp.front();
            tmp.pop();
            s.update(1,n,1,i,f.read(cover[i])-f.read(i-1));
        }
        for(auto i:v){
            int st=q[i][0]+1;
            int jump=q[i][1];
            int l=st-1,r=n;
            while(l<r){
                int m=(l+r+1)/2;
                if(f.read(m)-f.read(st-1)<=jump)l=m;
                else r=m-1;
            }
            int skip=s.query(1,n,1,st,l+1);
            l=st-1,r=n;
            while(l<r){
                int m=(l+r+1)/2;
                if(f.read(m)-f.read(st-1)<=jump+skip)l=m;
                else r=m-1;
            }
            Ans[i]=l;
        }
    }while(it!=mp.begin());
    return Ans;
}
