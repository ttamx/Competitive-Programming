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
    ll m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll k=(n+m+1)/2;
    auto check=[&](int mid){
        ll op=m,cnt=0;
        priority_queue<pair<ll,ll>> pq;
        ll f=0;
        for(auto x:a){
            if(x<mid)f+=x-1;
            else{
                pq.emplace(x,1);
                cnt++;
            }
        }
        while(!pq.empty()&&op>0){
            auto [v,c]=pq.top();
            if(v<mid*2)break;
            pq.pop();
            while(!pq.empty()&&pq.top().first==v){
                c+=pq.top().second;
                pq.pop();
            }
            ll t=min(op,c);
            cnt+=t;
            op-=t;
            if(t<c)pq.emplace(v,c-t);
            if(v%2==0){
                pq.emplace(v/2,t*2);
            }else{
                pq.emplace(v/2,t);
                pq.emplace(v/2+1,t);
            }
        }
        op-=f;
        while(!pq.empty()&&op>0&&cnt>=k){
            auto [v,c]=pq.top();
            pq.pop();
            while(!pq.empty()&&pq.top().first==v){
                c+=pq.top().second;
                pq.pop();
            }
            if((v+1)/2==mid){
                op-=c;
                continue;
            }
            ll t=min((op-1)/(v-1)+1,c);
            op-=t*(v-1);
            cnt-=t;
        }
        return cnt>=k&&op<=0;
    };
    int l=1,r=1e9;
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}