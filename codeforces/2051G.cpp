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
    vector<pair<int,char>> a(m);
    for(auto &[x,y]:a){
        cin >> x >> y;
        x--;
    }
    vector<vector<int>> b(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j)continue;
            int p=0,l=1,r=1;
            for(auto [x,y]:a){
                if(x==i){
                    if(y=='+'){
                        p++;
                        if(p==l){
                            l++,r++;
                        }
                    }
                }else if(x==j){
                    if(y=='+'){
                        r++;
                    }else{
                        l++;
                    }
                }
            }
            b[i][j]=r-p;
        }
    }
    vector<int> pos(n);
    for(auto [x,y]:a){
        if(y=='+'){
            pos[x]++;
        }
    }
    vector<vector<int>> dp(1<<n,vector<int>(n,INF));
    for(int mask=1;mask<(1<<n);mask++){
        for(int i=0;i<n;i++){
            if(!(mask>>i&1))continue;
            int mask2=mask^(1<<i);
            if(!mask2){
                dp[mask][i]=pos[i];
                break;
            }
            for(int j=0;j<n;j++){
                if(!(mask2>>j&1))continue;
                dp[mask][i]=min(dp[mask][i],dp[mask2][j]+b[j][i]);
            }
        }
    }
    cout << *min_element(dp.back().begin(),dp.back().end())+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}