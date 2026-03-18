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

const int N=32;
const int K=440;

bool dp[N][K];
int pre[N][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[0][0]=true;
    for(int i=1;i<N;i++){
        for(int j=0;j<i;j++){
            int c=(i-j)*(i-j-1)/2;
            for(int k=0;k+c<K;k++){
                if(dp[j][k]){
                    dp[i][k+c]=true;
                    pre[i][k+c]=j;
                }
            }
        }
    }
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        k=n*(n-1)/2-k;
        if(!dp[n][k]){
            cout << 0 << "\n";
            continue;
        }
        int buf=0;
        vector<int> a;
        for(int i=n,j=k;i>0;){
            int ii=pre[i][j];
            int c=i-ii;
            buf+=c;
            for(int x=0;x<c;x++){
                a.emplace_back(buf-x);
            }
            i=ii;
            j-=c*(c-1)/2;
        }
        reverse(a.begin(),a.end());
        for(auto x:a){
            cout << x << " ";
        }
        cout << "\n";
    }
}