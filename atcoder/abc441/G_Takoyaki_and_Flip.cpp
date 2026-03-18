#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

const int N=2e5+5;
const int K=1<<19;

struct Tag{
    array<ll,2> add;
    array<bool,2> mod;
    bool sw;
    Tag():add{},mod{},sw(false){}
    void apply(const Tag &o){
        if(o.sw){
            sw^=true;
            swap(add[0],add[1]);
            swap(mod[0],mod[1]);
        }
        if(o.mod[0])add[0]=0,mod[0]=true;
        add[0]+=o.add[0];
        if(o.mod[1])add[1]=0,mod[1]=true;
        add[1]+=o.add[1];
    }
};

struct Segtree{
    pair<int,ll> t[K][2];
    Tag lz[K];
    void build(int l,int r,int i){
        t[i][0]={0,0};
        t[i][1]={1,0};
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void apply(int i,Tag v){
        if(v.sw)swap(t[i][0],t[i][1]);
        t[i][0].second=(v.mod[0]?0LL:t[i][0].second)+v.add[0];
        t[i][1].second=(v.mod[1]?0LL:t[i][1].second)+v.add[1];
        lz[i].apply(v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=Tag();
    }
    void update(int l,int r,int i,int x,int y,Tag v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i][0]=max(t[i*2][0],t[i*2+1][0]);
        t[i][1]=max(t[i*2][1],t[i*2+1][1]);
    }
    pair<int,ll> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {0LL,0LL};
        if(x<=l&&r<=y)return t[i][1];
        push(i);
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

void runcase(){
    int n,q;
    cin >> n >> q;
    seg.build(1,n,1);
    while(q--){
        int op,l,r;
        cin >> op >> l >> r;
        if(op==1){
            int x;
            cin >> x;
            Tag t;
            t.add[1]=x;
            seg.update(1,n,1,l,r,t);
        }else if(op==2){
            Tag t;
            t.sw=true;
            t.mod[0]=true;
            seg.update(1,n,1,l,r,t);
        }else{
            ll ans=0;
            auto v=seg.query(1,n,1,l,r);
            if(v.first)ans=max(ans,v.second);
            cout << ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}