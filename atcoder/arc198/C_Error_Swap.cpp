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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    if(accumulate(a.begin(),a.end(),0LL)!=accumulate(b.begin(),b.end(),0LL)){
        cout << "No\n";
        exit(0);
    }
    vector<pair<int,int>> ans;
    auto answer=[&](){
        cout << "Yes\n";
        cout << ans.size() << "\n";
        for(auto [x,y]:ans){
            cout << x+1 << " " << y+1 << "\n";
        }
        exit(0);
    };
    auto work=[&](int i,int j){
        assert(i<j);
        swap(a[i],a[j]);
        a[i]--,a[j]++;
        ans.emplace_back(i,j);
    };
    if(n==2){
        for(int t=0;t<2;t++){
            if(a==b)answer();
            work(0,1);
        }
        cout << "No\n";
        exit(0);
    }
    auto increase=[&](int i){
        assert(i+2<n);
        int j=max_element(a.begin()+i+2,a.end())-a.begin();
        int st=a[i];
        work(i,j-1);
        work(j-1,j);
        work(i,j);
        assert(a[i]==st+1);
    };
    auto decrease=[&](int i){
        assert(i+2<n);
        int j=min_element(a.begin()+i+1,a.end()-1)-a.begin();
        int st=a[i];
        work(i,j+1);
        work(j,j+1);
        work(i,j);
        assert(a[i]==st-1);
    };
    for(int i=0;i+2<n;i++){
        while(a[i]<b[i])increase(i);
        while(a[i]>b[i])decrease(i);
    }
    auto swapp=[&](){
        int i=n-2;
        work(i-1,i+1);
        work(i-1,i);
        work(i-1,i+1);
    };
    while(a[n-2]<b[n-2]){
        work(n-2,n-1);
        swapp();
    }
    while(a[n-2]>b[n-2]){
        swapp();
        work(n-2,n-1);
    }
    assert(a==b);
    answer();
}