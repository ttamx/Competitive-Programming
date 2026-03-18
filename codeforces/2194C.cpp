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
    int k,n;
    cin >> n >> k;
    vector<int> mask(n);
    for(int i=0;i<k;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++){
            mask[j]|=1<<(s[j]-'a');
        }
    }
    for(int i=1;i<=n;i++){
        if(n%i)continue;
        bool ok=true;
        string ans(n,'.');
        for(int s=0;s<i;s++){
            int cur=mask[s];
            for(int j=s;j<n;j+=i){
                cur&=mask[j];
            }
            if(!cur){
                ok=false;
                break;
            }
            int c=0;
            while(!(cur>>c&1))c++;
            for(int j=s;j<n;j+=i){
                ans[j]='a'+c;
            }
        }
        if(ok){
            cout << ans << "\n";
            return;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}