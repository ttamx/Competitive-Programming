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
    int n,m,k,s;
    cin >> n >> m >> k >> s;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> t(m),c(m);
    for(int i=0;i<m;i++){
        cin >> t[i] >> c[i];
    }
    vector<pair<int,int>> ans;
    auto check=[&](int x,bool save){
        int ai=min_element(a.begin(),a.begin()+x)-a.begin();
        int bi=min_element(b.begin(),b.begin()+x)-b.begin();
        ll ra=a[ai],rb=b[bi];
        vector<pair<ll,int>> d;
        for(int i=0;i<m;i++){
            d.emplace_back(c[i]*(t[i]==1?ra:rb),i);
        }
        sort(d.begin(),d.end());
        int cnt=0,budget=s;
        for(auto [x,i]:d){
            if(budget>=x){
                budget-=x;
                cnt++;
                if(save){
                    ans.emplace_back(i,t[i]==1?ai:bi);
                }
            }
        }
        return cnt>=k;
    };
    int l=1,r=n+1;
    while(l<r){
        int m=(l+r)/2;
        if(check(m,false))r=m;
        else l=m+1;
    }
    if(l>n){
        cout << -1 << "\n";
    }else{
        check(l,true);
        ans.resize(k);
        cout << l << "\n";
        for(auto [x,y]:ans){
            cout << x+1 << " " << y+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}