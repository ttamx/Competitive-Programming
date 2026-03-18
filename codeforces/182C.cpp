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
    int n,len;
    cin >> n >> len;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int k;
    cin >> k;
    ll ans=0;
    for(int t=0;t<2;t++){
        ll sum=0,cur=0;
        multiset<int> pql,pqr;
        for(int i=0;i<n;i++){
            sum+=a[i];
            if(i>=len&&a[i-len]<0){
                if(!pql.empty()&&a[i-len]<=*prev(pql.end())){
                    cur-=a[i-len];
                    pql.erase(pql.find(a[i-len]));
                }else{
                    pqr.erase(pqr.find(a[i-len]));
                }
                while(!pqr.empty()&&pql.size()<k){
                    int x=*pqr.begin();
                    cur+=x;
                    pql.emplace(x);
                    pqr.erase(pqr.begin());
                }
            }
            if(a[i]<0){
                cur+=a[i];
                pql.emplace(a[i]);
                while(pql.size()>k){
                    int x=*prev(pql.end());
                    cur-=x;
                    pqr.emplace(x);
                    pql.erase(prev(pql.end()));
                }
            }
            if(i>=len-1){
                ans=max(ans,sum-2*cur);
                sum-=a[i-len+1];
            }
        }
        for(auto &x:a){
            x=-x;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}