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
    int n,a,b;
    cin >> n >> a >> b;
    vector<int> v(n);
    for(auto &x:v){
        cin >> x;
    }
    vector<vector<int>> ans(a+1,vector<int>(b+1));
    vector<deque<tuple<int,int,int>>> qr(a+b+1);
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            qr[i+j].emplace_back(i,i,i);
        }
    }
    for(int s=0;s<=a+b;s++){
        auto &q=qr[s];
        int l=min(max(0,s-b),a),r=min(a,s);
        int z=0;
        auto work=[&](){
            {
                tuple<int,int,int> res(l,INF,-1);
                while(!q.empty()&&get<0>(q.front())<=l){
                    auto [p,l,r]=q.front();
                    q.pop_front();
                    get<1>(res)=min(get<1>(res),l);
                    get<2>(res)=max(get<2>(res),r);
                }
                if(get<2>(res)!=-1){
                    q.emplace_front(res);
                }
            }
            {
                tuple<int,int,int> res(r,INF,-1);
                while(!q.empty()&&get<0>(q.back())>=r){
                    auto [p,l,r]=q.back();
                    q.pop_back();
                    get<1>(res)=min(get<1>(res),l);
                    get<2>(res)=max(get<2>(res),r);
                }
                if(get<2>(res)!=-1){
                    q.emplace_back(res);
                }
            }
        };
        for(auto [p,l,r]:q){
            for(int i=l;i<=r;i++){
                ans[i][s-i]=p;
            }
        }
        work();
        for(auto x:v){
            l+=x,r+=x,z+=x;
            work();
        }
        for(auto [p,l,r]:q){
            for(int i=l;i<=r;i++){
                ans[i][s-i]=p-z;
            }
        }
    }
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            cout << ans[i][j] << " \n"[j==b];
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}