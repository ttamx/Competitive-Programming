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
    string s;
    cin >> n >> s;
    auto check=[&](int mid){
        int cover=-1;
        int star=-1;
        for(int i=0;i<n;i++){
            if(s[i]=='*'){
                if(i<=cover)continue;
                if(star==-1)star=i;
            }else if(s[i]=='P'){
                if(star==-1)cover=i+mid;
                else{
                    int d=i-star;
                    if(d>mid)return false;
                    int rem=(mid-d)/2;
                    rem=max(rem,mid-2*d);
                    cover=max(cover,i+rem);
                    star=-1;
                }
            }
        }
        return star<=cover;
    };
    int l=0,r=n*2;
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
    while(t--)runcase();
}