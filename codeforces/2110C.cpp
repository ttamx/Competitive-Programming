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
    vector<int> d(n);
    for(auto &x:d)cin >> x;
    int lo=0,hi=0;
    queue<int> q;
    vector<pair<int,int>> a(n);
    for(auto &[l,r]:a)cin >> l >> r;
    for(int i=0;i<n;i++){
        auto [l,r]=a[i];
        if(d[i]==-1){
            hi++;
            q.emplace(i);
        }else{
            lo+=d[i],hi+=d[i];
        }
        while(lo<l){
            if(q.empty()){
                cout << "-1\n";
                return;
            }
            int j=q.front();
            q.pop();
            d[j]=1;
            lo++;
        }
        while(hi>r){
            if(q.empty()){
                cout << "-1\n";
                return;
            }
            int j=q.front();
            q.pop();
            d[j]=0;
            hi--;
        }
        if(lo>hi){
            cout << "-1\n";
            return;
        }
    }
    while(!q.empty()){
        d[q.front()]=0;
        q.pop();
    }
    for(auto x:d){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}