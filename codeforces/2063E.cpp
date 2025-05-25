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
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct Info{
    ll sum;
    int cnt;
    Info():sum(0),cnt(0){}
    Info(ll sum,int cnt):sum(sum),cnt(cnt){}
    friend Info operator+(const Info &a,const Info &b){
        return Info(a.sum+b.sum,a.cnt+b.cnt);
    }
};

struct Treap{
    struct Node{
        Info val,sum;
        int key,prio,sz;
        int l,r;
        Node(Info v,int k):val(v),sum(v),key(k),prio(rng()),sz(1),l(-1),r(-1){}
    };
    vector<ll> vals;
    vector<Node> node;
    int root;
    ll sum,cnt,lz;
    Treap():root(-1),sum(0LL),cnt(0LL),lz(0LL){}
    int newnode(Info v,int key){
        node.emplace_back(v,key);
        return node.size()-1;
    }
    int size(int x){
        return x==-1?0:node[x].sz;
    }
    Info get_sum(int x){
        return x==-1?Info():node[x].sum;
    }
    void pull(int x){
        node[x].sz=size(node[x].l)+size(node[x].r)+1;
        node[x].sum=node[x].val+get_sum(node[x].l)+get_sum(node[x].r);
    }
    void split(int t,int &l,int &r,int key){
        if(t==-1){
            l=r=-1;
            return;
        }
        if(node[t].key<=key){
            l=t;
            split(node[t].r,node[t].r,r,key);
            pull(l);
        }else{
            r=t;
            split(node[t].l,l,node[t].l,key);
            pull(r);
        }
    }
    int merge(int &t,int l,int r){
        if(l==-1||r==-1){
            t=l==-1?r:l;
            return t;
        }
        if(node[l].prio>node[r].prio){
            t=l;
            merge(node[t].r,node[l].r,r);
        }else{
            t=r;
            merge(node[t].l,l,node[r].l);
        }
        pull(t);
        return t;
    }
    void insert(int key,Info val){
        sum+=key;
        cnt++;
        key-=lz;
        val.sum-=lz;
        vals.emplace_back(key);
        int l,r;
        split(root,l,r,key);
        merge(l,l,newnode(val,key));
        merge(root,l,r);
    }
    Info query(int l,int r){
        l-=lz,r-=lz;
        int x,y,z;
        split(root,x,y,l-1);
        split(y,y,z,r);
        Info res=get_sum(y);
        merge(y,y,z);
        merge(root,x,y);
        return res;
    }
    void add_all(ll val){
        sum+=cnt*val;
        lz+=val;
    }
    void clear(){
        vals.clear();
        node.clear();
        root=-1;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ll ans=0;
    vector<Treap> ds(n);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            ll delta=ds[v].sum*ds[u].cnt+ds[u].sum*ds[v].cnt-ds[u].cnt*ds[v].cnt;
            ans+=ds[u].sum*ds[v].cnt+ds[v].sum*ds[u].cnt-ds[u].cnt*ds[v].cnt;
            if(ds[v].node.size()>ds[u].node.size()){
                swap(ds[u],ds[v]);
            }
            for(auto x:ds[v].vals){
                x+=ds[v].lz;
                Info ql=ds[u].query(-INF,x);
                Info qr=ds[u].query(x+1,INF);
                ans-=x*ql.cnt-ql.sum-ql.cnt*ds[u].lz;
                ans-=qr.sum+qr.cnt*ds[u].lz-x*qr.cnt;
            }
            for(auto x:ds[v].vals){
                ds[u].insert(x+ds[v].lz,Info(x+ds[v].lz,1));
            }
            ds[v].clear();
        }
        ds[u].insert(0,Info(0,1));
        ds[u].add_all(1);
    };
    dfs(0,-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}