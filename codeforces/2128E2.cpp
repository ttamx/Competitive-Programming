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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto [v1,l1,r1]=[&](){
        auto calc=[&](int mid){
            vector<int> b(n+1);
            int mn=INF,idx=-1;
            int l=-1,r=-1;
            for(int i=0;i<n;i++){
                b[i+1]=b[i]+(a[i]<=mid?1:-1);
            }
            for(int i=k;i<=n;i++){
                if(b[i-k]<mn){
                    idx=i-k;
                    mn=b[i-k];
                }
                if(b[i]-mn>=0){
                    return make_pair(idx,i-1);
                }
            }
            return make_pair(-1,-1);
        };
        int l=1,r=n;
        while(l<r){
            int mid=(l+r)/2;
            if(calc(mid).first!=-1)r=mid;
            else l=mid+1;
        }
        auto [vl,vr]=calc(l);
        return make_tuple(l,vl,vr);
    }();
    auto [v2,l2,r2]=[&](){
        auto calc=[&](int mid){
            vector<int> b(n+1);
            int mn=INF,idx=-1;
            int l=-1,r=-1;
            for(int i=0;i<n;i++){
                b[i+1]=b[i]+(a[i]>=mid?1:-1);
            }
            for(int i=k;i<=n;i++){
                if(b[i-k]<mn){
                    idx=i-k;
                    mn=b[i-k];
                }
                if(b[i]-mn>=0){
                    return make_pair(idx,i-1);
                }
            }
            return make_pair(-1,-1);
        };
        int l=1,r=n;
        while(l<r){
            int mid=(l+r+1)/2;
            if(calc(mid).first!=-1)l=mid;
            else r=mid-1;
        }
        auto [vl,vr]=calc(l);
        return make_tuple(l,vl,vr);
    }();
    vector<tuple<int,int,int>> ans;
    multiset<int> ml,mr;
    auto rebalance=[&](){
        if(ml.size()>mr.size()){
            mr.emplace(*prev(ml.end()));
            ml.erase(prev(ml.end()));
        }
        if(mr.size()>ml.size()+1){
            ml.emplace(*mr.begin());
            mr.erase(mr.begin());
        }
    };
    auto insert=[&](int x){
        if(mr.empty()||x>=*mr.begin())mr.emplace(x);
        else ml.emplace(x);
        rebalance();
    };
    auto erase=[&](int x){
        if(x>=*mr.begin()){
            mr.extract(x);
        }else{
            ml.extract(x);
        }
        rebalance();
    };
    for(int i=l1;i<=r1;i++){
        insert(a[i]);
    }
    while(v1<=v2){
        while(v1<=*mr.begin()){
            ans.emplace_back(v1++,l1,r1);
        }
        if(l1>l2){
            insert(a[--l1]);
        }else if(r1<r2){
            insert(a[++r1]);
        }else if(l1<l2){
            erase(a[l1++]);
        }else if(r1>r2){
            erase(a[r1--]);
        }
    }
    cout << ans.size() << "\n";
    for(auto [v,l,r]:ans){
        cout << v << " " << l+1 << " " << r+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}