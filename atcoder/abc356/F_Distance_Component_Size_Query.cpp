#include<bits/stdc++.h>
#include<bits/extc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

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
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

void runcase(){
    int q;
    ll k;
    cin >> q >> k;
    set<ll> s,sr,sl;
    ordered_set<ll> f;
    while(q--){
        int t;
        ll x;
        cin >> t >> x;
        if(t==1){
            auto [it,added]=s.emplace(x);
            if(added){
                f.insert(x);
                if(next(it)!=s.end()&&it!=s.begin()){
                    ll l=*prev(it),r=*next(it);
                    if(r-l>k){
                        sl.erase(sl.find(l));
                        sr.erase(sr.find(r));
                    }
                }
                if(next(it)!=s.end()){
                    ll r=*next(it);
                    if(r-x>k){
                        sl.insert(x);
                        sr.insert(r);
                    }
                }
                if(it!=s.begin()){
                    ll l=*prev(it);
                    if(x-l>k){
                        sl.insert(l);
                        sr.insert(x);
                    }
                }
            }else{
                it=s.find(x);
                f.erase(f.find(x));
                if(next(it)!=s.end()){
                    ll r=*next(it);
                    if(r-x>k){
                        sl.erase(sl.find(x));
                        sr.erase(sr.find(r));
                    }
                }
                if(it!=s.begin()){
                    ll l=*prev(it);
                    if(x-l>k){
                        sl.erase(sl.find(l));
                        sr.erase(sr.find(x));
                    }
                }
                if(next(it)!=s.end()&&it!=s.begin()){
                    ll l=*prev(it),r=*next(it);
                    if(r-l>k){
                        sl.insert(l);
                        sr.insert(r);
                    }
                }
                s.erase(it);
            }
        }else{
            int ans=0;
            auto l=sr.upper_bound(x);
            if(l!=sr.begin())ans-=f.order_of_key(*prev(l));
            auto r=sl.lower_bound(x);
            if(r!=sl.end())ans+=f.order_of_key(*r)+1;
            else ans+=sz(s);
            cout << ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}