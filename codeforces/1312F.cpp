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
    int n,d[3];
    cin >> n >> d[0] >> d[1] >> d[2];
    vector<array<int,3>> grundy(501,{-1,-1,-1});
    function<int(ll,int)> calc=[&](ll i,int j){
        if(i<=0)return 0;
        if(grundy[i][j]!=-1)return grundy[i][j];
        vector<bool> seen(5);
        for(int x=0;x<3;x++){
            if(x==0||x!=j){
                seen[calc(i-d[x],x)]=1;
            }
        }
        int mex=0;
        while(seen[mex])mex++;
        return grundy[i][j]=mex;
    };
    int pr=0;
    while(true){
        pr++;
        bool ok=true;
        for(int i=200;i<=500;i++){
            for(int j=0;j<3;j++){
                if(calc(i,j)!=calc(i-pr,j)){
                    ok=false;
                    break;
                }
            }
            if(!ok){
                break;
            }
        }
        if(ok)break;
    };
    function<int(ll,int)> calc2=[&](ll i,int j){
        if(i>500)i-=((i-501)/pr+1)*pr;
        return calc(i,j);
    };
    int nimber=0;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
        nimber^=calc2(x,0);
    }
    int ans=0;
    for(auto &x:a){
        nimber^=calc2(x,0);
        for(int i=0;i<3;i++){
            if(nimber==calc2(x-d[i],i)){
                ans++;
            }
        }
        nimber^=calc2(x,0);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}