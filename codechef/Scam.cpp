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
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    map<int,int> cnt;
    for(auto &x:a){
        cin >> x;
        if(x!=-1){
            cnt[x]++;
        }
    }
    vector<tuple<int,int,int>> b;
    for(auto [v,c]:cnt){
        if(v!=m){
            for(int i=0;i<c;i++){
                b.emplace_back(i,c,v);
            }
        }
    }
    int c=cnt[m];
    cnt.clear();
    int mx=0;
    vector<int> best;
    map<int,int> cnt2;
    auto upd=[&](int x){
        cnt[x]++;
        cnt2[x]++;
        if(cnt[x]>mx){
            mx=cnt[x];
            best={x};
        }else if(cnt[x]==mx){
            best.emplace_back(x);
        }
    };
    for(int i=0;i<n;i++){
        if(a[i]==-1){
            if(best.size()==1){
                cnt2[best[0]]++;
            }
        }else if(c>0){
            upd(m);
            c--;
        }else{
            upd(get<2>(b.back()));
            b.pop_back();
        }
    }
    int t=cnt2[m];
    for(auto [x,v]:cnt2){
        if(x!=m&&v>=t){
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}