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
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i=0;i<n;i++)a[i]=(s[i]=='('?1:-1);
    tuple<int,int,int> ans(0,0,0);
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            swap(a[i],a[j]);
            vector<int> pre(n),suf(n);
            int bal=0;
            for(int i=0;i<n;i++){
                bal+=a[i];
                if(i+1<n)pre[i+1]=bal;
                suf[i]=bal;
            }
            for(int i=1;i<n;i++)pre[i]=min(pre[i],pre[i-1]);
            for(int i=n-2;i>=0;i--)suf[i]=min(suf[i],suf[i+1]);
            int cnt=0;
            if(bal==0){
                for(int i=0;i<n;i++){
                    if(suf[i]-bal>=0&&pre[i]-bal>=0)cnt++;
                    bal+=a[i];
                }
            }
            ans=max(ans,make_tuple(cnt,i,j));
            swap(a[i],a[j]);
        }
    }
    auto [v,i,j]=ans;
    cout << v << "\n";
    cout << i+1 << " " << j+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}