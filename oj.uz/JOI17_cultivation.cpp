#include<bits/stdc++.h>

using namespace std;

const int N=605;
const int K=1<<11;

struct SegTree{
    int n;
    int t[K],lz[K];
    void build(int l,int r,int i){
        t[i]=lz[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void init(int _n){
        n=_n;
        build(0,n-1,1);
    }
    void push(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(0,n-1,1,x,y,v);
    }
}seg;

int n,r,c;
int x[N],y[N];

bool check(int xl,int xr,int yl,int yr){
    vector<int> xs,ys;
    for(int i=0;i<n;i++){
        xs.emplace_back(max(1,x[i]-xl));
        xs.emplace_back(min(r,x[i]+xr));
        xs.emplace_back(min(r,max(1,x[i]-xl)+1));
        xs.emplace_back(max(1,min(c,x[i]+xr)-1));
        ys.emplace_back(max(1,y[i]-yl));
        ys.emplace_back(min(c,y[i]+yr));
        ys.emplace_back(min(c,max(1,y[i]-yl)+1));
        ys.emplace_back(max(1,min(c,y[i]+yr)-1));
    }
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    int xn=xs.size();
    int yn=ys.size();
    vector<vector<tuple<int,int,int>>> event(xn);
    for(int i=0;i<n;i++){
        int xi=lower_bound(xs.begin(),xs.end(),max(1,x[i]-xl))-xs.begin();
        int xj=lower_bound(xs.begin(),xs.end(),min(r,x[i]+xr))-xs.begin();
        int yi=lower_bound(ys.begin(),ys.end(),max(1,y[i]-yl))-ys.begin();
        int yj=lower_bound(ys.begin(),ys.end(),min(c,y[i]+yr))-ys.begin();
        event[xi].emplace_back(yi,yj+1,1);
        if(xj+1<xn){
            event[xi+1].emplace_back(yi,yj,-1);
        }
    }
    seg.init(yn);
    for(int i=0;i<xn;i++){
        for(auto [l,r,v]:event[i]){
            seg.update(l,r,v);
        }
        if(seg.t[1]==0)return false;
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    vector<int> xls,xrs,yls,yrs;
    for(int i=0;i<n;i++){
        xls.emplace_back(x[i]-1);
        xrs.emplace_back(r-x[i]);
        yls.emplace_back(y[i]-1);
        yrs.emplace_back(c-y[i]);
    }
    sort(xls.begin(),xls.end());
    sort(xrs.begin(),xrs.end());
    sort(yls.begin(),yls.end());
    sort(yrs.begin(),yrs.end());
    xls.erase(unique(xls.begin(),xls.end()),xls.end());
    xrs.erase(unique(xrs.begin(),xrs.end()),xrs.end());
    yls.erase(unique(yls.begin(),yls.end()),yls.end());
    yrs.erase(unique(yrs.begin(),yrs.end()),yrs.end());
    int ans=r+c-2;
    for(int xl:xls){
        for(int xr:xrs){
            for(int yl:yls){
                for(int yr:yrs){
                    if(check(xl,xr,yl,yr)){
                        cerr << xl << " " << xr << " " << yl << " " << yr << "\n";
                        ans=min(ans,xl+xr+yl+yr);
                    }
                }
            }
        }
    }
    cout << ans;
}