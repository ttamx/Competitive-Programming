#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast,unroll-loops")

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

const int N=1e6+5;

int z[N];
pair<int,int> st[N];

void runcase(){
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    while(q--){
        int lo,hi;
        cin >> lo >> hi;
        lo--;
        int m=hi-lo;
        z[0]=m;
        for(int i=1,l=0,r=0;i<m;i++){
            int k=i<r?min(z[i-l],r-i):0;
            while(i+k<m&&s[lo+k]==s[lo+i+k])k++;
            if(i+k>r)l=i,r=i+k;
            z[i]=k;
        }
        z[m]=0;
        ll res=0;
        int top=0;
        st[top]={1,m};
        for(int i=0;i<m;i++){
            while(st[top].second<i)top--;
            int cur=st[top].first;
            res+=cur;
            int j=i+z[i+1];
            while(st[top].second<j)top--;
            st[++top]={cur+1,j};
        }
        cout << res << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}