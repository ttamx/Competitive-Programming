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

int nimber[100];

int grundy(int n){
    if(n>86){
        n-=(n-86+33)/34*34;
    }
    return nimber[n];
}

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int ca=0,cb=0;
    for(auto x:s){
        if(x=='R')ca++;
        else cb++;
    }
    if(ca>cb){
        cout << "Alice\n";
        return;
    }
    if(ca<cb){
        cout << "Bob\n";
        return;
    }
    int nim=0;
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&s[j]!=s[j+1]){
            j++;
        }
        nim^=grundy(j-i+1);
        i=j;
    }
    cout << (nim>0?"Alice":"Bob") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<100;i++){
        vector<int> a;
        for(int j=0;j+2<=i;j++){
            a.emplace_back(nimber[j]^nimber[i-j-2]);
        }
        int k=a.size();
        vector<bool> seen(k+1);
        for(auto x:a){
            if(x<=k){
                seen[x]=true;
            }
        }
        int mex=0;
        while(seen[mex]){
            mex++;
        }
        nimber[i]=mex;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}