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
    auto ask=[&](int i,int j){
        assert(i<j);
        cout << "? " << i+1 << " " << j+1 << endl;
        string s;
        cin >> s;
        return s=="YES";
    };
    vector<int> black,white,both;
    vector<int> col(n,-1);
    black.emplace_back(0);
    for(int i=1;i<n;i++){
        if(both.empty()){
            if(ask(black.back(),i)){
                if(!white.empty()&&ask(white.back(),i)){
                    both.emplace_back(i);
                }else{
                    black.emplace_back(i);
                }
            }else{
                white.emplace_back(i);
            }
        }else{
            if(ask(both.back(),i)){
                both.emplace_back(i);
            }else{
                if(ask(black.back(),i)){
                    black.emplace_back(i);
                    white.insert(white.end(),both.begin(),both.end());
                }else{
                    white.emplace_back(i);
                    black.insert(black.end(),both.begin(),both.end());
                }
                both.clear();
            }
        }
    }
    white.insert(white.end(),both.begin(),both.end());
    for(auto i:black){
        col[i]=0;
    }
    for(auto i:white){
        col[i]=1;
    }
    cout << "!";
    for(auto x:col){
        cout << " " << x;
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}