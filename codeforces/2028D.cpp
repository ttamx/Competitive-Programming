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
    vector<vector<int>> a(3,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    vector<set<pair<int,int>>> s(3);
    for(int i=0;i<3;i++){
        s[i].emplace(a[i][0],0);
    }
    vector<int> p(n,-1),who(n,-1);
    for(int i=1;i<n;i++){
        for(int j=0;j<3;j++){
            auto it=s[j].upper_bound(make_pair(a[j][i],i));
            if(it!=s[j].end()){
                p[i]=it->second;
                who[i]=j;
            }
        }
        if(p[i]!=-1){
            for(int j=0;j<3;j++){
                s[j].emplace(a[j][i],i);
            }
        }
    }
    if(p[n-1]==-1){
        cout << "NO\n";
    }else{
        cout << "YES\n";
        vector<pair<int,int>> ans;
        for(int i=n-1;i>0;i=p[i]){
            ans.emplace_back(i,who[i]);
        }
        reverse(ans.begin(),ans.end());
        cout << ans.size() << "\n";
        for(auto [x,y]:ans){
            cout << "qkj"[y] << " " << x+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}