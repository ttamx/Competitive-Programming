#include<bits/stdc++.h>
#include "fatigue.h"

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=20;

int n;
int a[N],b[N],w[N];
int pos[N];
int spmn[K][N],spmx[K][N];

struct fenwick{
    ll t[N];
    void add(int i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f,f2;

int rmnq(int l,int r){
    int k=31-__builtin_clz(r-l+1);
    return min(spmn[k][l],spmn[k][r-(1<<k)+1]);
}

int rmxq(int l,int r){
    int k=31-__builtin_clz(r-l+1);
    return max(spmx[k][l],spmx[k][r-(1<<k)+1]);
}

ll calc(int l,int r){
    ll vl=f.read(l-1),vl2=f2.read(l-1);
    ll vr=f.read(r),vr2=f2.read(r);
    ll tar=(vl+vr+1)/2;
    while(l<r){
        int m=(l+r)/2;
        if(f.read(m)>=tar)r=m;
        else l=m+1;
    }
    ll vm=f.read(l),vm2=f2.read(l);
    return (vm-vl)*b[l]-(vm2-vl2)+(vr2-vm2)-(vr-vm)*b[l];
}

void initialize(int N, vector<int> A, vector<int> W){
    n=N;
    for(int i=1;i<=n;i++)a[i]=b[i]=A[i-1],w[i]=W[i-1];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        pos[i]=spmn[0][i]=spmx[0][i]=lower_bound(b+1,b+n+1,a[i])-b;
        f.add(pos[i],w[i]);
        f2.add(pos[i],1ll*a[i]*w[i]);
    }
    for(int i=1;i<K;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            spmn[i][j]=min(spmn[i-1][j],spmn[i-1][j+(1<<(i-1))]);
            spmx[i][j]=max(spmx[i-1][j],spmx[i-1][j+(1<<(i-1))]);
        }
    }
}

void change_weight(int X, int V){
    X++;
    ll d=V-w[X];
    w[X]+=d;
    f.add(pos[X],d);
    f2.add(pos[X],a[X]*d);
}

ll point_fatigue(vector<int> B){
    int l=n,r=1;
    for(auto x:B){
        x++;
        l=min(l,pos[x]);
        r=max(r,pos[x]);
    }
    return calc(l,r);
}

ll interval_fatigue(vector<vector<int>> In){
    int l=n,r=1;
    for(auto v:In){
        int x=v[0]+1,y=v[1]+1;
        l=min(l,rmnq(x,y));
        r=max(r,rmxq(x,y));
    }
    return calc(l,r);
}