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
    ll fac=1;
    for(int i=1;i<=n&&fac<=1e9;i++){
        fac*=i;
    }
    if(fac<k){
        cout << "NO\n";
        return;
    }
    map<vector<int>,bool> mp;
    if(n==1){
        cout << "YES\n";
        cout << "1\n";
        return;
    }
    if(k==1||(1LL*(n+1)*k)%2!=0){
        cout << "NO\n";
        return;
    }
    if(k%2==0){
        vector<int> a(n);
        iota(a.begin(),a.end(),1);
        cout << "YES\n";
        for(int i=0;i<k;i+=2){
            for(int t=0;t<2;t++){
                for(auto x:a){
                    cout << x << " ";
                }
                cout << "\n";
                for(auto &x:a){
                    x=n+1-x;
                }
            }
            next_permutation(a.begin(),a.end());
        }
        return;
    }
    if(k>fac-3){
        cout << "NO\n";
        return;
    }
    if(n==3){
        cout << "YES\n";
        cout << "1 2 3\n";
        cout << "2 3 1\n";
        cout << "3 1 2\n";
        return;
    }
    cout << "YES\n";
    vector<int> a;
    auto ban=[&](){
        for(int t=0;t<2;t++){
            mp[a]=true;
            for(auto &x:a){
                x=n+1-x;
            }
        }
    };
    for(int i=1;i<=n;i++){
        a.emplace_back(i);
        cout << i << " \n"[i==n];
    }
    ban();
    a.clear();
    int r=n,l=n/2;
    for(int i=1;i<=n;i++){
        if(i&1){
            a.emplace_back(r);
            cout << r--;
        }else{
            a.emplace_back(l);
            cout << l--;
        }
        cout << " \n"[i==n];
    }
    ban();
    a.clear();
    r=n,l=n/2+1;
    for(int i=1;i<=n;i++){
        if(i&1){
            a.emplace_back(l);
            cout << l--;
        }else{
            a.emplace_back(r);
            cout << r--;
        }
        cout << " \n"[i==n];
    }
    ban();
    k-=3;
    iota(a.begin(),a.end(),1);
    for(int i=0;i<k;i+=2){
        while(mp[a]){
            next_permutation(a.begin(),a.end());
        }
        for(int t=0;t<2;t++){
            for(auto x:a){
                cout << x << " ";
            }
            cout << "\n";
            for(auto &x:a){
                x=n+1-x;
            }
        }
        ban();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}