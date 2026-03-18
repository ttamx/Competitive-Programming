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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int> dat{0},par{0};
    for(int i=1;i<=20;i++){
        if(i!=(i&-i)){
            dat.emplace_back(i);
        }else{
            par.emplace_back(i);
        }
    }
    string phase;
    cin >> phase;
    if(phase[0]=='f'){
        int t;
        cin >> t;
        while(t--){
            int x;
            cin >> x;
            x--;
            vector<int> a;
            vector<int> val(21);
            for(int i=0;i<15;i++){
                if(x>>i&1){
                    a.emplace_back(dat[i+1]);
                    val[dat[i+1]]=1;
                }
            }
            for(int i=1;i<=5;i++){
                int x=0;
                for(int j=1;j<=20;j++){
                    if((j&par[i])&&val[j]){
                        x^=1;
                    }
                }
                if(x){
                    a.emplace_back(par[i]);
                }
            }
            cout << a.size() << "\n";
            for(auto x:a){
                cout << x << " ";
            }
            cout << "\n";
        }
    }else{
        int t;
        cin >> t;
        while(t--){
            int n;
            cin >> n;
            int pos=0;
            vector<int> val(21);
            for(int i=0;i<n;i++){
                int x;
                cin >> x;
                val[x]=1;
                pos^=x;
            }
            val[pos]^=1;
            int x=0;
            for(int i=1;i<=15;i++){
                if(val[dat[i]]){
                    x|=(1<<(i-1));
                }
            }
            cout << x+1 << "\n";
        }
    }
}