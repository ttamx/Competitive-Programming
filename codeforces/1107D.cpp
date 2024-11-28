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
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &x:a){
        string s;
        cin >> s;
        for(int i=0;i<n;i+=4){
            int v;
            if(isdigit(s[i/4])){
                v=s[i/4]-'0';
            }else{
                v=s[i/4]-'A'+10;
            }
            for(int j=0;j<4;j++){
                x[i+j]=(v>>(3-j))&1;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i>0)a[i][j]+=a[i-1][j];
            if(j>0)a[i][j]+=a[i][j-1];
            if(i>0&&j>0)a[i][j]-=a[i-1][j-1];
        }
    }
    for(int d=n;d>=2;d--){
        if(n%d)continue;
        bool ok=true;
        for(int i=d-1;i<n;i+=d){
            for(int j=d-1;j<n;j+=d){
                int sum=a[i][j];
                if(i>=d)sum-=a[i-d][j];
                if(j>=d)sum-=a[i][j-d];
                if(i>=d&&j>=d)sum+=a[i-d][j-d];
                if(sum!=0&&sum!=d*d){
                    ok=false;
                    break;
                }
            }
            if(!ok)break;
        }
        if(ok){
            cout << d << "\n";
            return;
        }
    }
    cout << 1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}