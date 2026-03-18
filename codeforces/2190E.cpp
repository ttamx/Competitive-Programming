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
    vector<bool> mark(n+1);
    for(auto &x:a){
        cin >> x;
        mark[x]=true;
    }
    vector<int> b;
    for(int i=1;i<=n;i++){
        if(!mark[i]){
            b.emplace_back(i);
        }
    }
    do{
        auto c=a;
        int p=0;
        for(auto &x:c){
            if(!x){
                x=b[p++];
            }
        }
        vector<int> d;
        vector<int> mark(n+1);
        bool ok=true;
        for(int i=2;i<n;i++){
            vector<int> e{c[i-2],c[i-1],c[i]};
            sort(e.begin(),e.end());
            d.emplace_back(e[1]);
            if(mark[e[1]])ok=false;
            mark[e[1]]=true;
        }
        if(ok){
            for(auto x:c){
                cerr << x << " ";
            }
            cerr << "\n";
        }
    }while(next_permutation(b.begin(),b.end()));
    cerr << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}