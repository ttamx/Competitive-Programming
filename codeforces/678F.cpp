#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

const int N=3e5+5;
const int K=1<<20;

int n;
int op[N],a[N],b[N],l[N],r[N];
vector<ll> xs;
ll ans[N];

struct Line{
    ll m,c;
    Line():m(0),c(-INF){}
    Line(ll m,ll c):m(m),c(c){}
    ll eval(ll x){
        return m*x+c;
    }
};

struct LiChaoTree{
    Line t[K];
    vector<ll> xs;
    vector<tuple<int,int,Line>> upd;
    int timer;
    void init(vector<ll> a){
        xs=a;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
        upd.clear();
        timer=0;
    }
    void backup(int i){
        upd.emplace_back(timer,i,t[i]);
    }
    void insert(int l,int r,int i,Line v){
        int m=(l+r)/2;
        if(v.eval(xs[m])>t[i].eval(xs[m])){
            backup(i);
            swap(t[i],v);
        }
        if(v.eval(xs[l])>t[i].eval(xs[l]))insert(l,m,i*2,v);
        if(v.eval(xs[r])>t[i].eval(xs[r]))insert(m+1,r,i*2+1,v);
    }
    void insert(Line v){
        timer++;
        insert(0,xs.size()-1,1,v);
    }
    ll query(int l,int r,int i,ll x){
        if(xs[r]<x||x<xs[l])return -INF;
        ll v=t[i].eval(x);
        if(l==r)return v;
        int m=(l+r)/2;
        return max({v,query(l,m,i*2,x),query(m+1,r,i*2+1,x)});
    }
    ll query(ll x){
        return query(0,xs.size()-1,1,x);
    }
    void roll_back(){
        timer--;
        while(!upd.empty()&&get<0>(upd.back())>timer){
            auto [_,i,v]=upd.back();
            upd.pop_back();
            t[i]=v;
        }
    }
}seg;

vector<pair<int,int>> t[K];

void insert(int l,int r,int i,int x,int y,int a,int b){
    if(y<l||r<x)return;
    if(x<=l&&r<=y)return void(t[i].emplace_back(a,b));
    int m=(l+r)/2;
    insert(l,m,i*2,x,y,a,b);
    insert(m+1,r,i*2+1,x,y,a,b);
}

void solve(int l,int r,int i){
    for(auto [a,b]:t[i])seg.insert(Line(a,b));
    if(l==r){
        if(op[l]==3){
            ans[l]=seg.query(a[l]);
        }
    }else{
        int m=(l+r)/2;
        solve(l,m,i*2);
        solve(m+1,r,i*2+1);
    }
    for(auto [a,b]:t[i])seg.roll_back();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> op[i];
        if(op[i]==1){
            cin >> a[i] >> b[i];
            l[i]=i;
            r[i]=n;
        }else if(op[i]==2){
            int x;
            cin >> x;
            r[x]=i;
        }else{
            cin >> a[i];
            xs.emplace_back(a[i]);
        }
    }
    for(int i=1;i<=n;i++){
        if(op[i]==1){
            insert(1,n,1,l[i],r[i],a[i],b[i]);
        }
    }
    xs.emplace_back(0);
    seg.init(xs);
    solve(1,n,1);
    for(int i=1;i<=n;i++){
        if(op[i]==3){
            if(ans[i]==-INF){
                cout << "EMPTY SET\n";
            }else{
                cout << ans[i] << "\n";
            }
        }
    }
}