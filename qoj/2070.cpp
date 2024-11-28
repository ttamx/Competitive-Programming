#include<bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=2e5+5;

int n;
ll a[N];
vector<int> add[N],del[N];

struct Info{
    ll c0,c1,ans,l,r;
    Info():c0(0),c1(0),ans(0){}
    Info(ll _c0,ll _c1,ll _ans,int _l,int _r):c0(_c0),c1(_c1),ans(_ans),l(_l),r(_r){}
    bool operator<(const Info &o)const{
        ll v0=c1*o.c0,v1=c0*o.c1;
        return v0<v1||(v0==v1&&c1<o.c1);
    }
    friend Info operator+(const Info &lhs,const Info &rhs){
        return Info(lhs.c0+rhs.c0,lhs.c1+rhs.c1,lhs.ans+rhs.ans+lhs.c1*rhs.c0,min(lhs.l,rhs.l),max(lhs.l,rhs.r));
    }
};

struct SegTree{
    int n;
    vector<Info> t;
    void init(int _n){
        n=_n;
        int s=1;
        while(s<n)s*=2;
        t.assign(s*2,Info());
    }
    void modify(int l,int r,int i,int x,Info v){
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,Info v){
        modify(0,n-1,1,x,v);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    vector<tuple<Info,int,int>> b;
    {
        vector<pair<Info,int>> s;
        for(int i=1;i<=n;i++){
            Info cur(a[i],1,a[i],i,i);
            while(!s.empty()&&cur<s.back().first){
                auto [o,st]=s.back();
                s.pop_back();
                cur=o+cur;
                b.emplace_back(o,st,i);
            }
            s.emplace_back(cur,i+1);
        }
        for(auto [o,st]:s){
            b.emplace_back(o,st,n);
        }
    }
    {
        vector<pair<Info,int>> s;
        for(int i=n;i>=1;i--){
            Info cur(a[i],1,a[i],i,i);
            while(!s.empty()&&cur<s.back().first){
                auto [o,ed]=s.back();
                s.pop_back();
                cur=o+cur;
                b.emplace_back(o,i,ed);
            }
            s.emplace_back(cur,i-1);
        }
        for(auto [o,ed]:s){
            b.emplace_back(o,1,ed);
        }
    }
    int m=b.size();
    seg.init(m);
    sort(b.begin(),b.end());
    for(int i=0;i<m;i++){
        auto [o,st,ed]=b[i];
        if(st<=ed){
            add[st].emplace_back(i);
            del[ed].emplace_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto j:add[i]){
            seg.modify(j,get<0>(b[j]));
        }
        cout << seg.t[1].ans+(n-1)*a[i] << " ";
        for(auto j:del[i]){
            seg.modify(j,Info());
        }
    }
}