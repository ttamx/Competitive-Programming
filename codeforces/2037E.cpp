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
    auto ask=[&](int l,int r){
        cout << "? " << l+1 << " " << r+1 << endl;
        ll res;
        cin >> res;
        return res;
    };
    bool ok=false;
    ll pre=ask(0,1);
    string s="XX";
    if(pre==1){
        ok=true;
        s="01";
    }
    for(int i=2;i<n;i++){
        ll tmp=ask(0,i);
        if(tmp==pre){
            if(ok){
                s+='0';
            }else{
                s+='X';
            }
        }else{
            if(!ok){
                for(int j=0;j<tmp-pre;j++){
                    s[s.size()-1-j]='0';
                }
                for(int j=tmp-pre;j<s.size();j++){
                    s[s.size()-1-j]='1';
                }
                ok=true;
            }
            s+='1';
        }
        pre=tmp;
    }
    if(s[0]=='X'){
        s="IMPOSSIBLE";
    }
    cout << "! " << s << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}