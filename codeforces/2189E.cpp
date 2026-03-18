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
    string s;
    cin >> s;
    int c=count(s.begin(),s.end(),'1');
    if(c==0){
        cout << -1 << "\n";
        return;
    }
    if(n==1){
        cout << 0 << "\n";
        return;
    }
    if(c*2>=n){
        cout << n << "\n";
        return;
    }
    if(n==3){
        cout << n+1 << "\n";
        return;
    }
    {
        int mn=0,mx=0,cur=0;
        for(auto x:s){
            cur+=(x=='0'?1:-1);
            mn=min(mn,cur);
            mx=max(mx,cur-mn);
        }
        cur-=max(mx-1,1);
        if(cur<=0){
            cout << n+1 << "\n";
            return;
        }
    }
    for(int t=0;t<2;t++){
        int cur=0;
        for(auto x:s){
            cur+=(x=='1'?1:-1);
            if(cur>=0){
                cout << n+2 << "\n";
                return;
            }
        }
        reverse(s.begin(),s.end());
    }
    int mn=0,cur=0;
    for(auto x:s){
        cur+=(x=='1'?1:-1);
        if(cur-mn>=2){
            cout << n+2 << "\n";
            return;
        }
        mn=min(mn,cur);
    }
    cout << n+3 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}