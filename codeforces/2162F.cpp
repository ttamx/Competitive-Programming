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
    int n,m;
    cin >> n >> m;
    vector<int> c(n),st(n),ed(n);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        l--;
        c[l]++;
        st[l]=1;
        if(r<n){
            c[r]--;
            ed[r]=1;
        }
    }
    for(int i=1;i<n;i++){
        c[i]+=c[i-1];
    }
    vector<int> ans(n,-1);
    auto answer=[&](int st){
        for(auto &x:ans){
            if(x==-1){
                x=st++;
            }
        }
        for(auto x:ans){
            cout << x << " ";
        }
        cout << "\n";
    };
    for(int i=0;i<n;i++){
        if(c[i]==m){
            ans[i]=0;
            answer(1);
            return;
        }
    }
    for(int i=0;i+1<n;i++){
        if(!st[i+1]){
            ans[i]=1;
            ans[i+1]=0;
            answer(2);
            return;
        }
        if(!ed[i+1]){
            ans[i]=0;
            ans[i+1]=1;
            answer(2);
            return;
        }
    }
    ans[0]=0;
    ans[1]=2;
    ans[2]=1;
    answer(3);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}