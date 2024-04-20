#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

void runcase(){
    int n,k;
    cin >> n >> k;
    k--;
    vi a(n);
    for(auto &x:a)cin >> x;
    auto calc=[&](int pos){
        swap(a[k],a[pos]);
        int mx=0,res=0;
        for(int i=0;i<pos;i++)mx=max(mx,a[i]);
        if(pos>0&&a[pos]>mx)res++;
        if(a[pos]>mx)for(int i=pos+1;i<n&&a[pos]>a[i];i++)res++;
        swap(a[k],a[pos]);
        return res;
    };
    int ans=max(calc(k),calc(1));
    for(int i=0;i<n;i++){
        if(a[k]<a[i]){
            ans=max(ans,calc(i));
            break;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}