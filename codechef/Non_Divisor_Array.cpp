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
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> p(n);
    int ans=1;
    for(int i=1;i<=n;i++)for(int j=i+i;j<=n;j+=i)p[j-1].emplace_back(i-1);
    vector<int> used(n+1);
    for(int i=0;i<n;i++){
        for(auto j:p[i])used[a[j]]=true;
        int val=1;
        while(used[val])val++;
        for(auto j:p[i])used[a[j]]=false;
        ans=max(ans,val);
        a[i]=val;
    }
    cout << ans << "\n";
    for(auto x:a)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}