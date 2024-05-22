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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vi a(m);
    for(auto &x:a)cin >> x;
    sort(rall(a));
    if(a.back()==1)cout << -1,exit(0);
    vi ans;
    vector<bool> used(n+2);
    for(int i=1;i<=n;i++)if(!used[i]){
        int p=i;
        while(!a.empty()&&p==a.back()){
            ans.emplace_back(++p);
            used[p]=true;
            a.pop_back();
        }
        ans.emplace_back(i);
        used[i]=true;
    }
    if(used[n+1])cout << -1;
    else for(auto x:ans)cout << x << " ";
}