#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;
const int INF=INT_MAX/2;

int n;
int a[N];
int l[N],r[N],d[N];
bool mark[N];
vector<int> ord;
ll ans;

struct SegmentTree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v,lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void build(int l,int r,int i){
        t[i]=INF;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){build(1,n,1);}
    void modify(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i]=v);
        push(i);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void modify(int x,int v){modify(1,n,1,x,v);}
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){update(1,n,1,x,y,v);};
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INF;
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){return query(1,n,1,x,y);}
}seg;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}fen;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]>0){
            ans+=a[i];
            ord.emplace_back(i);
        }
    }
    l[0]=-INF,r[n+1]=INF;
    for(int i=1;i<=n;i++){
        l[i]=a[i]==-1?i:l[i-1];
    }
    for(int i=n;i>=1;i--){
        r[i]=a[i]==-1?i:r[i+1];
    }
    for(int i=1;i<=n;i++){
        d[i]=min(i-l[i],r[i]-i);
    }
    sort(ord.rbegin(),ord.rend(),[&](int i,int j){
        return d[i]<d[j]||(d[i]==d[j]&&i<j);
    });
    seg.build();
    for(auto i:ord){
        if(r[i]==INF||mark[r[i]])continue;
        mark[i]=true;
        ans--;
        a[i]--;
        seg.modify(i,i-1);
    }
    reverse(ord.begin(),ord.end());
    for(auto i:ord){
        if(!a[i])continue;
        int t=min({seg.query(i,n),2*(i-1)-fen.query(i),a[i]})/(2*d[i]);
        if(t<=0)continue;
        ans-=t;
        seg.update()
    }
    cout << ans << "\n";
}