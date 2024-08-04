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
    vector<vector<int>> pos(n+1);
    for(int i=1;i<=n;i++)pos[i].emplace_back(-1);
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    for(int i=1;i<=n;i++)pos[i].emplace_back(n);
    vector<int> ans(n+1,n+1);
    for(int i=n;i>=1;i--)if(pos[i].size()>2){
        int mx=0;
        for(int j=1;j<pos[i].size();j++){
            mx=max(mx,pos[i][j]-pos[i][j-1]);
        }
        ans[mx]=i;
    }
    for(int i=2;i<=n;i++)ans[i]=min(ans[i],ans[i-1]);
    for(int i=1;i<=n;i++)cout << (ans[i]>n?-1:ans[i]) << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}