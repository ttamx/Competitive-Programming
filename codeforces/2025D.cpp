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
    vector<int> dp(m+1),add(m+2);
    int cnt=0;
    auto work=[&](){
        int v=0;
        for(int i=0;i<=m;i++){
            v+=add[i];
            add[i]=0;
            dp[i]+=v;
        }
    };
    while(n--){
        int r;
        cin >> r;
        if(r==0){
            cnt++;
            if(cnt>2*m)continue;
            work();
            for(int i=min(m,cnt);i>=1;i--){
                dp[i]=max(dp[i],dp[i-1]);
            }
        }else if(r>0){
            add[r]++;
            add[min(m,cnt)+1]--;
        }else{
            r=-r;
            add[0]++;
            add[max(min(m,cnt-r)+1,0)]--;
        }
    }
    work();
    cout << *max_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}