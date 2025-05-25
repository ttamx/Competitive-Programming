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
    string s;
    cin >> s;
    int n=s.size();
    int l=0,r=n-1;
    while(l<r&&s[l]==s[r]){
        l++,r--;
    }
    if(l>=r){
        cout << 0 << "\n";
        return;
    }
    s=s.substr(l,r-l+1);
    n=s.size();
    auto check=[&](int k){
        auto ss=s;
        for(int t=0;t<2;t++){
            vector<int> cnt(30);
            for(int i=0;i<n;i++){
                if(i<k){
                    cnt[ss[i]-'a']++;
                }else{
                    cnt[ss[i]-'a']--;
                }
            }
            if(*min_element(cnt.begin(),cnt.end())>=0){
                return true;
            }
            reverse(ss.begin(),ss.end());
        }
        return false;
    };
    l=n/2,r=n;
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    int ans=l;
    int ml=n/2-1;
    int mr=ml+1;
    while(s[ml]==s[mr]){
        ml--;
        mr++;
    }
    string a=s.substr(0,ml+1);
    string b=s.substr(mr,s.size()-mr);
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    if(a==b){
        ans=min(ans,(int)a.size());
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}