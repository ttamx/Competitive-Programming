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
    int k;
    cin >> k;
    string s,t;
    cin >> s >> t;
    int n=s.size(),m=t.size();
    if(abs(n-m)>1){
        cout << "No\n";
        return;
    }
    if(n==m){
        int cnt=0;
        for(int i=0;i<n;i++){
            cnt+=s[i]!=t[i];
        }
        cout << (cnt<=1?"Yes":"No") << "\n";
        return;
    }
    int lcp=0,lcs=0;
    while(lcp<min(n,m)&&s[lcp]==t[lcp])lcp++;
    while(lcs<min(n,m)&&s[n-lcs-1]==t[m-lcs-1])lcs++;
    cout << (lcp+lcs>=min(n,m)?"Yes":"No") << "\n";

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}