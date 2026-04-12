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
        ll sum,mx;
        Ptr l,r;
        Node():sum(0),mx(0),l(),r(){}
    };
    Ptr root;
    int ans;
    Segtree():root(),ans(INF){}
    ll get_mx(Ptr t){
        return t?t->mx:0;
    }
    ll get_sum(Ptr t){
        return t?t->sum:0;
    }
    Ptr get_l(Ptr t){
        return t?t->l:nullptr;
    }
    Ptr get_r(Ptr t){
        return t?t->r:nullptr;
    }
    void update(int l,int r,Ptr &t,Ptr tl,Ptr tr,int x,int y,ll v,ll al,ll ar){
        if(y<l||r<x)return;
        if(!t)t=new Node();
        if(x<=l&&r<=y){
            t->sum+=v;
        }else{
            int m=(l+r)/2;
            update(l,m,t->l,get_l(tl),get_l(tr),x,y,v,al+get_sum(tl),ar+get_sum(tr));
            update(m+1,r,t->r,get_r(tl),get_r(tr),x,y,v,al+get_sum(tl),ar+get_sum(tr));
        }
        t->mx=max({get_mx(t->l),get_mx(t->r),get_mx(tl)+al,get_mx(tr)+ar})+t->sum;
        cerr << "\tD: " << get_mx(t->l) << " " << get_mx(t->r) << " " << get_mx(tl)+al << " " << get_mx(tr)+ar << " | " << t->sum << "\n";
        cerr << "\t" << l << " " << r << " : " << t->mx << "\n";
    }
    int query(int l,int r,Ptr t,Ptr tl,Ptr tr,ll tar,ll al,ll ar){
        tar-=get_sum(t);
        ll mx=max({get_mx(get_l(t)),get_mx(get_r(t)),get_mx(tl)+al,get_mx(tr)+ar});
        if(mx<tar)return INF;
        if(l==r)return l;
        al+=get_sum(tl);
        ar+=get_sum(tr);
        int m=(l+r)/2;
        int res=query(l,m,get_l(t),get_l(tl),get_l(tr),tar,al,ar);
        if(res<INF)return res;
        return query(m+1,r,t->r,get_r(tl),get_r(tr),tar,al,ar);
    }
    void update(Ptr tl,Ptr tr,int x,ll v){
        cerr << "\tPRE : " << get_mx(root) << "\n";
        update(1,n,root,tl,tr,x,n,v,0,0);
        ans=query(1,n,root,tl,tr,k,0,0);
        cerr << "\tUPDATE " << x << " " << v << " : " << ans << "\n";
        dfs(1,n,root,tl,tr,x,n,v,0,0);
    }
    void dfs(int l,int r,Ptr &t,Ptr tl,Ptr tr,int x,int y,ll v,ll al,ll ar){
        if(!t)t=new Node();
        if(l<r){
            int m=(l+r)/2;
            dfs(l,m,t->l,get_l(tl),get_l(tr),x,y,v,al+get_sum(tl),ar+get_sum(tr));
            dfs(m+1,r,t->r,get_r(tl),get_r(tr),x,y,v,al+get_sum(tl),ar+get_sum(tr));
        }
        ll mx=max({get_mx(t->l),get_mx(t->r),get_mx(tl)+al,get_mx(tr)+ar})+t->sum;
        cerr << "\tD: " << get_mx(t->l) << " " << get_mx(t->r) << " " << get_mx(tl)+al << " " << get_mx(tr)+ar << " | " << t->sum << "\n";
        cerr << "\t" << l << " " << r << " : " << t->mx << "\n";
    }
};

struct Segtree2{
    Segtree t[K];
    void update(int l,int r,int i,int x,int y,int key,ll val){
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            cerr << "RANGE " << l << " " << r << "\n";
            t[i].update(t[i*2].root,t[i*2+1].root,key,val);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,key,val);
        update(m+1,r,i*2+1,x,y,key,val);
        cerr << "RANGE " << l << " " << r << "\n";
        t[i].update(t[i*2].root,t[i*2+1].root,key,0);
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
        row[i]=seg.t[1].ans;
        cerr << "AT " << xs[i] << " : " << row[i] << "\n";
        cerr << "-------\n";
    }
    for(int i=1;i<=w+1;i++){
        for(auto j:event2[i]){
            if(j>0){
                seg.update(1,w,1,lef[j],rig[j],j,a[j]);
            }else{
                j=-j;
                seg.update(1,w,1,lef[j],rig[j],j,-a[j]);
            }
        }
        col[i]=seg.t[1].ans;
    }
    for(int i=0;i<=n;i++){
        mnh[i]=INF;
        mxh[i]=-INF;
        mnw[i]=INF;
        mxw[i]=-INF;
    }
    for(int i=1;i<=h;i++){
        int t=row[i];
        if(t<=n){
            mnh[t]=min(mnh[t],(ll)xs[i]);
            mxh[t]=max(mxh[t],(ll)xs[i]);
        }
    }
    for(int i=1;i<=w;i++){
        int t=col[i];
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
        cout << max(mxh[i]-mnh[i]+1,0LL)*max(mxw[i]-mnw[i]+1,0LL) << "\n";
    }
}