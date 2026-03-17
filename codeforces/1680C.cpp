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
    int c[2]={};
    for(auto x:s){
        c[x-'0']++;
    }
    auto check=[&](int m){
        int c1=c[1],c0=0;
        for(int l=0,r=0;r<n;r++){
            if(s[r]=='1'){
                c1--;
            }else{
                c0++;
                while(c0>m){
                    if(s[l]=='0'){
                        c0--;
                    }else{
                        c1++;
                    }
                    l++;
                }
            }
            if(c1<=m){
                return true;
            }
        }
        return false;
    };
    int l=0,r=n;
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}