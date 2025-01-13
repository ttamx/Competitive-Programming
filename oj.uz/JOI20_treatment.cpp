#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const ll INF=LLONG_MAX/2;

struct Info{
    int x,y,id;
    bool real;
    bool operator<(const Info &o)const{
        if(x!=o.x)return x<o.x;
        if(y!=o.y)return y<o.y;
        return !real&&o.real;
    }
};
jk
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> m >> n;
    vector<int> t(n),l(n),r(n),c(n);
    for(int i=0;i<n;i++){
        cin >> t[i] >> l[i] >> r[i] >> c[i];
    }
    vector<vector<int>> adj(n);
    auto new_node=[&](){
        adj.emplace_back(vector<int>());
        return (int)adj.size()-1;
    };
    auto link=[&](int u,int v){
        if(u!=-1&&v!=-1)adj[u].emplace_back(v);
    };
    vector<Info> a(2*n),b(2*n);
    vector<int> in(2*n),out(2*n);
    auto rec=[&](auto &&self,int l,int r){
        if(l==r)return;
        int m=(l+r)/2;
        self(self,l,m);
        self(self,m+1,r);
        in[l]=a[l].real?-1:a[l].id;
        for(int i=l+1;i<=m;i++){
            link(in[i]=new_node(),in[i-1]);
            if(!a[i].real)link(in[i],a[i].id);
        }
        out[m+1]=a[m+1].real?a[m+1].id:-1;
        for(int i=m+2;i<=r;i++){
            link(out[i]=new_node(),out[i-1]);
            if(a[i].real)link(a[i].id,out[i]);
        }
        for(int i=l,j=m+1,p=l;p<=r;p++){
            if(j>r||(i<=m&&a[i].y<=a[j].y)){
                b[p]=a[i];
                i++;
            }else{
                b[p]=a[j];
                if(i>l)link(out[j],in[i-1]);
                j++;
            }
        }
        for(int i=l;i<=r;i++)a[i]=b[i];
    };
    for(int i=0;i<n;i++){
        a[i*2]={-t[i],r[i]+t[i],i,true};
        a[i*2+1]={-t[i],l[i]+t[i]-1,i,false};
    }
    sort(a.begin(),a.end());
    rec(rec,0,2*n-1);
    for(int i=0;i<n;i++){
        a[i*2]={t[i],r[i]-t[i],i,true};
        a[i*2+1]={t[i],l[i]-t[i]-1,i,false};
    }
    sort(a.begin(),a.end());
    rec(rec,0,2*n-1);
    vector<ll> dist(adj.size(),INF);
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=0;i<n;i++){
        if(l[i]==1){
            dist[i]=c[i];
            pq.emplace(c[i],i);
        }
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto v:adj[u]){
            ll nd=d+(v<n?c[v]:0);
            if(nd<dist[v]){
                dist[v]=nd;
                pq.emplace(nd,v);
            }
        }
    }
    ll ans=INF;
    for(int i=0;i<n;i++){
        if(r[i]==m){
            ans=min(ans,dist[i]);
        }
    }
    cout << (ans<INF?ans:-1LL);
}