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
    int cnt=0;
    auto ask=[&](int u,int v){
        cnt++;
        assert(cnt<=n*2-6);
        cout << "? " << u << " " << v << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> p(n);
    p[1]=0;
    deque<int> cand;
    int u=2;
    for(;u<n;u++){
        cand.emplace_front(u);
        if(ask(1,u)==0){
            p[u]=1;
            u++;
            break;
        }
    }
    for(;u<n;u++){
        for(int i=cand.size()-1;i>=0;i--){
            if(i==0||ask(u,cand[i])==0){
                p[u]=cand[i];
                while(cand.size()>i){
                    cand.pop_back();
                }
                cand.emplace_front(u);
                break;
            }
        }
    }
    cout << "!";
    for(int i=1;i<n;i++){
        cout << " " << p[i];
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}