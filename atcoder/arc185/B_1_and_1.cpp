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
    reverse(a.begin(),a.end());
    stack<pair<ll,ll>> s;
    ll left=0;
    for(auto x:a){
        x+=left;
        left=0;
        if(!s.empty()&&s.top().first<x){
            left=x-s.top().first;
            x-=left;
        }
        ll sum=x;
        ll cnt=1;
        while(!s.empty()&&s.top().first>=(sum+cnt-1)/cnt){
            auto [h,w]=s.top();
            s.pop();
            sum+=h*w;
            cnt+=w;
        }
        if(sum%cnt==0){
            s.emplace(sum/cnt,cnt);
        }else{
            s.emplace(sum/cnt+1,sum%cnt);
            s.emplace(sum/cnt,cnt-sum%cnt);
        }
    }
    cout << (left>0?"No":"Yes") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}