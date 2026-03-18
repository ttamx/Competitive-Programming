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
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.emplace_back(x,i);
    }
    sort(a.rbegin(),a.rend());
    a.emplace_back(0,-1);
    int opt1=0,opt2=1,opt3=3;
    auto get=[&](int i){
        return a[i].first-a[i+1].first;
    };
    for(int i=0;i<n;i++){
        deque<pair<int,int>> dq;
        int p=i+2;
        for(int j=i+1;j<n;j++){
            if((j-i)*2<i+1)continue;
            if(j-i>2*(i+1))continue;
            int mn=min(i+1,j-i);
            int mx=max(i+1,j-i);
            int l=(mx+1)/2;
            int r=mn*2;
            while(p<n&&p-j<=r){
                int v=get(p);
                while(!dq.empty()&&dq.back().first<=v){
                    dq.pop_back();
                }
                dq.emplace_back(v,p);
                p++;
            }
            while(!dq.empty()&&dq.front().second-j<l){
                dq.pop_front();
            }
            if(!dq.empty()){
                int k=dq.front().second;
                if(make_tuple(get(i),get(j),get(k))>make_tuple(get(opt1),get(opt2),get(opt3))){
                    opt1=i;
                    opt2=j;
                    opt3=k;
                }
            }
        }
    }
    vector<int> ans(n,-1);
    for(int i=0;i<=opt1;i++){
        ans[a[i].second]=1;
    }
    for(int i=opt1+1;i<=opt2;i++){
        ans[a[i].second]=2;
    }
    for(int i=opt2+1;i<=opt3;i++){
        ans[a[i].second]=3;
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}