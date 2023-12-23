#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n,k;
    cin >> n >> k;
    vl a(n);
    for(auto &x:a)cin >> x;
    if(k>2)return void(cout << "0\n");
    sort(all(a));
    ll ans=a[0];
    for(int i=1;i<n;i++)ans=min(ans,a[i]-a[i-1]);
    if(k==1)return void(cout << ans << "\n");
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        ll v=a[j]-a[i];
        auto it=upper_bound(all(a),v);
        if(it!=a.begin())ans=min(ans,v-*prev(it));
        it=lower_bound(all(a),v);
        if(it!=a.end())ans=min(ans,*it-v);
    }
    cout << ans << "\n"
;}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}