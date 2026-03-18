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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int add=(6-a[0]%6)%6;
    for(auto &x:a){
        x+=add;
        if(x%6){
            cout << -1 << "\n";
            return;
        }
        x/=6;
    }
    sort(a.rbegin(),a.rend());
    function<int(vector<int>)> rec=[&](vector<int> a){
        while(!a.empty()&&a.back()==0)a.pop_back();
        if(a.empty())return 0;
        vector<int> b[42];
        for(auto x:a){
            b[x%42].emplace_back(x/42);
        }
        int res=-1;
        for(int i=0;i<42;i++){
            bool ok=true;
            for(int j=7;j<42;j+=7){
                if(!b[(j-i+42)%42].empty()){
                    ok=false;
                    break;
                }
            }
            if(ok){
                int cur=rec(b[(42-i)%42]);
                if(cur==0)return i;
                if(cur!=-1){
                    cur=cur*42+i;
                    if(res==-1||cur<res){
                        res=cur;
                    }
                }
            }
            for(auto &x:b[41-i])x++;
        }
        return res;
    };
    int ans=rec(a);
    if(ans!=-1)ans=ans*6+add;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}