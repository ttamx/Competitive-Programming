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
    assert(n>=2*k);
    auto ask=[&](int x){
        cout << "? " << x+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](int x){
        if(x==-1)cout << "! -1" << endl;
        else cout << "! " << x << " " << n-x << endl;
    };
    if(n==2*k){
        answer(k);
        return;
    }
    vector<int> a(k),b(k);
    for(int i=0;i<k;i++)a[i]=ask(i);
    for(int i=n-k;i<n;i++)b[i%k]=ask(i);
    bool ok=false;
    int lo=k-1,hi=n-k;
    for(int s=0;s<k;s++){
        if(a[s]==b[s])continue;
        int l=1,r=(n-s-1)/k;
        while(l<r){
            int m=(l+r)/2;
            if(ask(m*k+s)==a[s])l=m+1;
            else r=m;
        }
        if(r*k+s>=n)continue;
        lo=max(lo,k*(l-1)+s);
        hi=min(hi,k*l+s);
        ok=true;
        break;
    }
    if(!ok){
        answer(-1);
    }else{
        vector<int> c(n);
        c[lo]=1;
        c[hi]=2;
        for(int i=lo+1;i<hi;i++){
            int t=ask(i);
            if(t==a[i%k])c[i]|=1;
            if(t==b[i%k])c[i]|=2;
        }
        auto pre=c,suf=c;
        for(int i=lo+1;i<hi;i++)pre[i]&=pre[i-1];
        for(int i=hi-1;i>lo;i--)suf[i]&=suf[i+1];
        int pos=-1;
        for(int i=lo;i<hi;i++){
            if((pre[i]&1)&&(suf[i+1]&2)){
                if(pos!=-1){
                    answer(-1);
                    return;
                }else{
                    pos=i+1;
                }
            }
        }
        answer(pos);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}