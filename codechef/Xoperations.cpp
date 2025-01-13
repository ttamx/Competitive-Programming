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

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    a.insert(a.begin(),0);
    struct Node{
        int cnt;
        array<int,2> ch;
        Node():cnt(0),ch{-1,-1}{}
    };
    vector<Node> node;
    auto new_node=[&](){
        node.emplace_back(Node());
        return (int)node.size()-1;
    };
    auto copy_node=[&](int i){
        if(i==-1)return new_node();
        node.emplace_back(node[i]);
        return (int)node.size()-1;
    };
    auto get_cnt=[&](int u){
        return u==-1?0:node[u].cnt;
    };
    auto get_ch=[&](int u,int c){
        return u==-1?-1:node[u].ch[c];
    };
    auto insert=[&](int p,ll x){
        int u=copy_node(p);
        int root=u;
        node[u].cnt++;
        for(int i=59;i>=0;i--){
            int c=x>>i&1;
            p=get_ch(p,c);
            node[u].ch[c]=copy_node(p);
            u=node[u].ch[c];
            node[u].cnt++;
        }
        return root;
    };
    auto query=[&](int ul,int ur,ll x){
        ll res=0;
        for(int i=59;i>=0;i--){
            int c=x>>i&1;
            if(get_cnt(get_ch(ur,c^1))-get_cnt(get_ch(ul,c^1))>0){
                ul=get_ch(ul,c^1);
                ur=get_ch(ur,c^1);
                res|=1LL<<i;
            }else{
                ul=get_ch(ul,c);
                ur=get_ch(ur,c);
            }
        }
        return res;
    };
    vector<int> root(n+1,-1);
    for(int i=1;i<=n;i++){
        root[i]=insert(root[i-1],a[i]);
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        int l=i+1,r=i+2,sz=2;
        while(l<=n){
            r=min(r,n);
            sz*=2;
            if(query(root[l-1],root[r],a[i])>=sz){
                int st=l;
                while(l<r){
                    int m=(l+r)/2;
                    if(query(root[st-1],root[m],a[i])>=sz)r=m;
                    else l=m+1;
                }
                break;
            }
            l=r+1;
            r=l+sz-1;
        }
        ans+=l-i;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}