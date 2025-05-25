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

struct DS{
    deque<ll> dq;
    ll ans,sum;
    int n;
    DS():dq(),ans(0LL),sum(0LL),n(0){}
    void push_back(ll x){
        n++;
        dq.emplace_back(x);
        sum+=x;
        ans+=x*n;
    }
    void push_front(ll x){
        n++;
        dq.emplace_front(x);
        sum+=x;
        ans+=sum;
    }
    ll pop_back(){
        ll x=dq.back();
        ans-=x*n;
        sum-=x;
        dq.pop_back();
        n--;
        return x;
    }
    ll pop_front(){
        ll x=dq.front();
        ans-=sum;
        sum-=x;
        dq.pop_front();
        n--;
        return x;
    }
};

void runcase(){
    int q;
    cin >> q;
    DS a,b;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            a.push_front(a.pop_back());
            b.push_back(b.pop_front());
        }else if(t==2){
            swap(a,b);
        }else{
            ll x;
            cin >> x;
            a.push_back(x);
            b.push_front(x);
        }
        cout << a.ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}