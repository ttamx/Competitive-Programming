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
    int l,r,sz;
    bool f;
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<Info> s;
    int tot=0;
    ll ans=0;
    for(auto x:a){
        Info cur{x,-1,0,false};
        while(!s.empty()&&s.back().r>=cur.l){
            auto e=s.back();
            s.pop_back();
            tot-=e.sz;
            if(cur.l==0)continue;
            if(e.f){
                cur.l--;
                int v=min((e.r-1)/2,cur.l);
                int d=cur.l-v;
                if(cur.r==-1)cur.r=v;
                else cur.r-=d;
                cur.l=v;
                cur.sz++;
            }else{
                cur.sz+=e.sz;
                int d=e.r-cur.l+1;
                e.r-=d,e.l-=d;
                if(e.l<0){
                    cur.sz+=e.l;
                    e.l=0;
                }
                if(cur.r==-1)cur.r=e.r;
                cur.l=e.l;
            }
        }
        if(cur.sz)s.emplace_back(cur);
        s.emplace_back(Info{x,x,1,true});
        tot+=cur.sz+1;
        ans+=tot;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}