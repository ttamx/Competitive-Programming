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
    ll k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    ll sum=0,mn=0,best=0;
    vector<int> pos;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            sum+=a[i];
            best=max(best,sum-mn);
            mn=min(mn,sum);
        }else{
            sum=mn=0;
            pos.emplace_back(i);
        }
    }
    const ll S=-1e18;
    if(best==k){
        cout << "Yes\n";
        for(int i=0;i<n;i++){
            cout << (s[i]=='1'?a[i]:S) << " \n"[i==n-1];
        }
        return;
    }
    if(best>k||pos.empty()){
        cout << "No\n";
        return;
    }
    auto calc=[&](int l,int p,int r){
        ll res=0;
        {
            ll sum=0,best=0;
            for(int i=p-1;i>=l;i--){
                sum+=a[i];
                best=max(best,sum);
            }
            res+=best;
            cerr << best << " ";
        }
        {
            ll sum=0,best=0;
            for(int i=p+1;i<=r;i++){
                sum+=a[i];
                best=max(best,sum);
            }
            res+=best;
        }
        return res;
    };
    for(int i=1;i<pos.size();i++){
        a[pos[i]]=S;
    }
    if(pos.size()==1){
        pos.emplace_back(n);
    }
    a[pos[0]]=k-calc(0,pos[0],pos[1]-1);
    cout << "Yes\n";
    for(auto x:a){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}