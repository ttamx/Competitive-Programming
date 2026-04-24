#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<int> x1(n),x2(n),y1(n),y2(n);
    for(int i=0;i<n;i++){
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }
    auto xs=x1;xs.insert(xs.end(),ALL(x2));
    auto ys=y1;ys.insert(ys.end(),ALL(y2));
    SORT(xs);UNI(xs);
    SORT(ys);UNI(ys);
    for(auto &x:x1)x=LB(xs,x);
    for(auto &x:x2)x=LB(xs,x);
    for(auto &y:y1)y=LB(ys,y);
    for(auto &y:y2)y=LB(ys,y);
    vector<vector<int>> event(2*n);
    for(int i=0;i<n;i++){
        event[y1[i]].eb(i);
    }
    vector<int> id(2*n,-1),a(n);
    vector<bool> bad(n);
    for(auto &v:event){
        for(auto i:v){
            int val=-1;
            for(int j=x1[i];j<x2[i];j++){
                int k=id[j];
                if(k!=1&&bad[k]){
                    if(val==-1)val=a[k];
                    if(val!=a[k]){
                        cout << "NO\n";
                        return;
                    }
                }
            }
            if(val==-1)val=y1[i];
            for(int j=x1[i];j<x2[i];j++){
                int k=id[j];
                if(k!=-1&&!bad[k]){
                    if(a[k]>val){
                        cout << "NO\n";
                        return;
                    }
                    bad[k]=true;
                    a[k]=val;
                }
                id[j]=i;
            }
            a[i]=y2[i];
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}