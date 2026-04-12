#include<bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=4e5+5;
const int K=1<<20;
const int INF=1e9;

int h,w,n;
ll k;
ll top[N],bot[N],lef[N],rig[N],a[N];
ll xs[N],ys[N];
vector<int> event1[N],event2[N];
int row[N],col[N];
ll mnh[N],mxh[N],mnw[N],mxw[N];
ll ans=0;

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll sum;
        Ptr l,r;
        Node():sum(0),l(),r(){}
    };
    Ptr root;
    int ans,mn;
    Segtree():root(),ans(INF),mn(INF){}
    void update(int l,int r,Ptr &t,int x,ll v){
        if(!t)t=new Node();
        t->sum+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void updaye(int x,ll v){
        update(1,n,root,x,v);
    }
};

struct Segtree2{
    Segtree t[K];
    void update(int l,int r,int i,int x,int y,int key,ll val){
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            t[i].update(key,val);
            if(l<r){
                t[i].mn=min({t[i].mn,t[i*2].mn,t[i*2+1].mn});
            }
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,key,val);
        update(m+1,r,i*2+1,x,y,key,val);
        t[i].mn=min({t[i].ans,t[i*2].mn,t[i*2+1].mn});
    }
    void dfs(int l,int r,int i){
        if(l==r)return;
        int m=(l+r)/2;
        dfs(l,m,i*2);
        dfs(m+1,r,i*2+1);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> h >> w >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> top[i] >> bot[i] >> lef[i] >> rig[i] >> a[i];
        xs[i*2-1]=top[i];
        xs[i*2]=bot[i];
        ys[i*2-1]=lef[i];
        ys[i*2]=rig[i];
    }
    sort(xs+1,xs+n*2+1);
    sort(ys+1,ys+n*2+1);
    h=unique(xs+1,xs+n*2+1)-xs-1;
    w=unique(ys+1,ys+n*2+1)-ys-1;
    for(int i=1;i<=n;i++){
        top[i]=lower_bound(xs+1,xs+h+1,top[i])-xs;
        bot[i]=lower_bound(xs+1,xs+h+1,bot[i])-xs;
        lef[i]=lower_bound(ys+1,ys+w+1,lef[i])-ys;
        rig[i]=lower_bound(ys+1,ys+w+1,rig[i])-ys;
    }
    for(int i=1;i<=n;i++){
        event1[top[i]].emplace_back(i);
        event1[bot[i]+1].emplace_back(-i);
        event2[lef[i]].emplace_back(i);
        event2[rig[i]+1].emplace_back(-i);
    }
    for(int i=1;i<=h+1;i++){
        for(auto j:event1[i]){
            if(j>0){
                seg.update(1,w,1,lef[j],rig[j],j,a[j]);
            }else{
                j=-j;
                seg.update(1,w,1,lef[j],rig[j],j,-a[j]);
            }
        }
        row[i]=seg.t[1].mn;
    }
    for(int i=1;i<=w+1;i++){
        for(auto j:event2[i]){
            if(j>0){
                seg.insert(1,h,1,top[j],bot[j],j,a[j]);
            }else{
                j=-j;
                seg.erase(1,h,1,top[j],bot[j],j);
            }
        }
        col[i]=seg.t[1].mn;
    }
    for(int i=0;i<=n;i++){
        mnh[i]=INF;
        mxh[i]=-INF;
        mnw[i]=INF;
        mxw[i]=-INF;
    }
    cerr << "ROW ";
    for(int i=1;i<=h;i++){
        int t=row[i];
        cerr << row[i] << " \n"[i==h];
        if(t<=n){
            mnh[t]=min(mnh[t],(ll)xs[i]);
            mxh[t]=max(mxh[t],(ll)xs[i]);
        }
    }
    cerr << "COL ";
    for(int i=1;i<=w;i++){
        int t=col[i];
        cerr << col[i] << " \n"[i==h];
        if(t<=n){
            mnw[t]=min(mnw[t],(ll)ys[i]);
            mxw[t]=max(mxw[t],(ll)ys[i]);
        }
    }
    for(int i=1;i<=n;i++){
        mnh[i]=min(mnh[i],mnh[i-1]);
        mxh[i]=max(mxh[i],mxh[i-1]);
        mnw[i]=min(mnw[i],mnw[i-1]);
        mxw[i]=max(mxw[i],mxw[i-1]);
        cerr << mnh[i] << " " << mxh[i] << " x " << mnw[i] << " " << mxw[i] << "\n";
        cout << max((mxh[i]-mnh[i])*(mxw[i]-mnw[i]),0LL) << "\n";
    }
}