#include<bits/stdc++.h>

using namespace std;

const int N=150005;
const int S=600;
const int B=1500;

int n,m,q;
int a[N];
vector<int> adj[N];
int id[N];
vector<tuple<int,int,int,int>> qr[B];
int cnt[2*N],sum[(2*N)>>9];
int st,ed;

inline void modify(int x,int v){
    cnt[x]+=v;
    sum[x>>9]+=v;
}

inline void update(int u){
    modify(a[u],-1);
    for(auto v:adj[u]){
        if(st<=v&&v<=ed){
            modify(a[v],-1);
            a[v]^=u;
            a[u]^=v;
            modify(a[v],+1);
        }
    }
    modify(a[u],+1);
}

inline int query(int k){
    for(int i=0;;i++){
        if(k>sum[i]){
            k-=sum[i];
        }else{
            for(int j=i<<9;;j++){
                k-=cnt[j];
                if(k<=0){
                    return j;
                }
            }
        }
    }
    return 0;
}

inline void work(int l,int r){
    while(st>l){
        modify(0,+1);
        st--;
        update(st);
    }
    while(ed<r){
        modify(0,+1);
        ed++;
        update(ed);
    }
    while(st<l){
        update(st);
        st++;
        modify(0,-1);
    }
    while(ed>r){
        update(ed);
        ed--;
        modify(0,-1);
    }
}

void runcase(){
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int buf=-1,cur=0,sz=S;
    for(int i=1;i<=n;i++){
        if(cur+adj[i].size()<=S&&sz<S){
            cur+=adj[i].size();
        }else{
            cur=adj[i].size();
            buf++;
            sz=0;
        }
        id[i]=buf;
        sz++;
    }
    cin >> q;
    for(int i=0;i<q;i++){
        int l,r,k;
        cin >> l >> r >> k;
        qr[id[l]].emplace_back(r,l,k,i);
    }
    st=0,ed=-1;
    vector<int> ans(q);
    for(int b=0;b<=buf;b++){
        auto &v=qr[b];
        sort(v.begin(),v.end());
        for(auto [r,l,k,i]:v){
            work(l,r);
            ans[i]=query(k);
        }
    }
    for(auto x:ans){
        cout << x << "\n";
    }
    for(int i=1;i<=n;i++){
        adj[i].clear();
        a[i]=0;
    }
    for(int i=0;i<=buf;i++){
        qr[i].clear();
    }
    for(int i=0;i<=2*n;i++){
        cnt[i]=0;
    }
    for(int i=0;i<=(2*n)>>9;i++){
        sum[i]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}