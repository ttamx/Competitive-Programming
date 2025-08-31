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
    ll sum=0,mx=0;
    for(auto &x:a){
        cin >> x;
        mx=max(mx,x);
        sum+=x;
    }
    if(sum%2==1||mx*2>sum){
        cout << -1 << "\n";
        return;
    }
    ll cur=0;
    int pos=-1;
    for(int i=0;i<n;i++){
        cur+=a[i];
        if(cur*2==sum){
            cout << 1 << "\n";
            for(auto x:a){
                cout << x << " ";
            }
            cout << "\n";
            return;
        }
        if(cur*2>=sum){
            pos=i;
            break;
        }
    }
    assert(pos!=-1);
    ll d=cur*2-sum;
    ll v=d/2;
    cout << 2 << "\n";
    vector<ll> b(n);
    b[pos]=v;
    a[pos]-=v;
    if(d<=cur){
        for(int i=pos-1;i>=0;i--){
            b[i]=min(a[i],v);
            a[i]-=b[i];
            v-=b[i];
        }
    }else{
        assert(d<=sum-cur);
        for(int i=pos+1;i<n;i++){
            b[i]=min(a[i],v);
            a[i]-=b[i];
            v-=b[i];
        }
    }
    for(auto x:b){
        cout << x << " ";
    }
    cout << "\n";
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