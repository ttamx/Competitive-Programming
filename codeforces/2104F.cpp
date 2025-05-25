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
    map<string,vector<int>> mp;
    if(n<10){
        cout << n << "\n";
        return;
    }
    string s=to_string(n);
    array<array<array<int,2>,2>,10> dp{};
    int ans=0;
    bool ff=false;
    int len=s.size();
    for(auto c:s){
        int v=c-'0';
        for(int d=1;d<10;d++){
            ans+=max(v-1,0)*(dp[d][0][0]+dp[d][0][1]);
            ans+=8*(dp[d][1][0]+dp[d][1][1]);
            if(len%2==1){
                ans+=(dp[d][1][0]+dp[d][1][1]);
                if(v>0)ans+=(dp[d][0][0]+dp[d][0][1]);
            }else{
                ans+=(dp[d][0][0]+dp[d][0][1]);
                ans+=(dp[d][1][0]+dp[d][1][1]);
            }
        }
        len--;
        array<array<array<int,2>,2>,10> ndp{};
        if(ff){
            for(int d=1;d<10;d++){
                ndp[d][1][1]++;
            }
        }else{
            for(int d=1;d<=v;d++){
                ndp[d][d<v][1]++;
            }
            ff=true;
        }
        for(int d=1;d<10;d++){
            for(int f=0;f<2;f++){
                ndp[d][f|(0<v)][1]+=dp[d][f][1];
                for(int dd=d;dd<10;dd++){
                    if(f||(dd<=v)){
                        ndp[dd][f|(dd<v)][0]+=dp[d][f][0]+dp[d][f][1];
                    }
                }
            }
        }
        dp=move(ndp);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}