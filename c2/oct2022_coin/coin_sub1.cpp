#include "coin.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

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
    int read(int l,int r){
        return read(r)-read(l-1);
    }
}f;

int n,t;
int a[N];
priority_queue<pair<int,int>> pq;

void initialize(int N,vector<int> Rail,int L){
    n=N,t=L;
    for(int i=1;i<=n;i++)a[i]=Rail[i-1];
}

vector<int> max_dist(vector<vector<int>> coin){
    int sz=coin.size();
    vector<int> ans;
    for(int i=1;i<=n;i++)if(a[i]>coin[0][2])f.add(i,1);
    for(int i=0;i<sz;i++){
        int st=coin[i][0]+1,hop=coin[i][1]+t;
        int l=st-1,r=n+1;
        while(l<r){
            int m=(l+r+1)/2;
            if(f.read(st,m)>hop)r=m-1;
            else l=m;
        }
        ans.emplace_back(l-1);
    }
    return ans;
}