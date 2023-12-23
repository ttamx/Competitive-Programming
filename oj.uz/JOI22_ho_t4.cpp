#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int M=2e5+5;
const int K=1<<18;
const int inf=1e9;

int n,m,k,q;
int a[M],b[M],mn[N],mx[N];

void genmin(){
    vector<int> st[N],ed[N];
    for(int i=1;i<=m;i++){
        if(a[i]<b[i])continue;
        st[max(a[i]-k+1,b[i])].emplace_back(i);
        ed[a[i]].emplace_back(i);
    }
    set<pair<int,int>> s;
    for(int i=1;i<=n;i++){
        for(auto j:st[i])s.emplace(b[j],j);
        mn[i]=s.empty()?i:s.begin()->first;
        for(auto j:ed[i])s.erase({b[j],j});
    }
}

void genmax(){
    vector<int> st[N],ed[N];
    for(int i=1;i<=m;i++){
        if(a[i]>b[i])continue;
        st[a[i]].emplace_back(i);
        ed[min(a[i]+k-1,b[i])].emplace_back(i);
    }
    set<pair<int,int>> s;
    for(int i=1;i<=n;i++){
        for(auto j:st[i])s.emplace(b[j],j);
        mx[i]=s.empty()?i:s.rbegin()->first;
        for(auto j:ed[i])s.erase({b[j],j});
    }
}

struct segtree{
    struct node{
        int l,r;
        node():l(inf),r(-inf){}
        node(int i):l(i),r(i){}
        node(int l,int r):l(l),r(r){}
        friend node operator+(node a,node b){
            return node(min(a.l,b.l),max(a.r,b.r)); 
        }
    }t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=node(mn[l],mx[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    node query(int x,int y){
        return query(1,n,1,x,y);
    }
}s[20];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> m;
    for(int i=1;i<=m;i++)cin >> a[i] >> b[i];
    genmin();
    genmax();
    s[0].build();
    for(int i=1;i<20;i++){
        for(int j=1;j<=n;j++){
            auto tmp=s[i-1].query(mn[j],mx[j]);
            mn[j]=tmp.l,mx[j]=tmp.r;
        }
        s[i].build();
    }
    cin >> q;
    while(q--){
        int st,ed;
        cin >> st >> ed;
        if(ed<mn[st]||mx[st]<ed){
            cout << -1 << "\n";
            continue;
        }
        int ans=0;
        int cl=st,cr=st;
        for(int i=19;i>=0;i--){
            auto tmp=s[i].query(cl,cr);
            if(tmp.l<=ed&&ed<=tmp.r)continue;
            ans|=1<<i;
            cl=tmp.l,cr=tmp.r;
        }
        cout << ans+1 << "\n";
    }
}