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

const ll LIM=2e18;

void runcase(){
    string s,t;
    cin >> t >> s;
    t=s+t;
    int n=s.size();
    int m=t.size();
    vector<array<ll,26>> a(n+1),b(m+1);
    a[0]=b[0]=array<ll,26>{};
    for(int i=1;i<=n;i++){
        a[i]=a[i-1];
        a[i][s[i-1]-'a']++;
    }
    for(int i=1;i<=m;i++){
        b[i]=b[i-1];
        b[i][t[i-1]-'a']++;
    }
    vector<ll> len(2);
    len[0]=n;
    len[1]=m;
    vector<array<ll,26>> f(2);
    f[0]=a[n];
    f[1]=b[m];
    for(int i=2;;i++){
        len.emplace_back(len[i-1]+len[i-2]);
        f.emplace_back(f[i-1]);
        for(int j=0;j<26;j++)f[i][j]+=f[i-2][j];
        if(len[i]>LIM)break;
    }
    auto calc=[&](ll x,int c){
        ll res=0;
        for(int i=len.size()-1;i>=1;i--){
            if(x>=len[i]){
                x-=len[i];
                res+=f[i][c];
            }
        }
        assert(x<m);
        return res+b[x][c];
    };
    int q;
    cin >> q;
    while(q--){
        ll l,r;
        char c;
        cin >> l >> r >> c;
        cout << calc(r,c-'a')-calc(l-1,c-'a') << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}