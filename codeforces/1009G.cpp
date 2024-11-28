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
    string s;
    cin >> s;
    array<int,64> cnt{},dp{};
    for(auto x:s){
        int c=x-'a';
        for(int i=0;i<64;i++){
            if(i>>c&1){
                cnt[i]++;
            }
        }
    }
    int n=s.size();
    vector<int> mask(n,63);
    int m;
    cin >> m;
    for(int i=0;i<m;i++){
        int x;
        string t;
        cin >> x >> t;
        x--;
        mask[x]=0;
        for(auto c:t){
            mask[x]|=1<<(c-'a');
        }
    }
    auto upd=[&](int i,int v){
        int s=mask[i];
        for(int b=0;b<64;b++){
            if(b&s){
                dp[b]+=v;
            }
        }
    };
    auto check=[&](){
        for(int b=1;b<64;b++){
            if(cnt[b]>dp[b]){
                return false;
            }
        }
        return true;
    };
    for(int i=0;i<n;i++){
        upd(i,+1);
    }
    if(!check()){
        cout << "Impossible\n";
        return;
    }
    string ans="";
    for(int i=0;i<n;i++){
        upd(i,-1);
        for(int j=0;j<6;j++){
            if(!(mask[i]>>j&1))continue;
            for(int b=0;b<64;b++){
                if(b>>j&1){
                    cnt[b]--;
                }
            }
            if(check()){
                ans+=char('a'+j);
                break;
            }
            for(int b=0;b<64;b++){
                if(b>>j&1){
                    cnt[b]++;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}