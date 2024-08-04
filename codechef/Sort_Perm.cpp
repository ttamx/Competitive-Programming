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
    for(auto &x:a)cin >> x;
    vector<vector<int>> seq{{a[0]}};
    for(int i=1;i<n;i++){
        if(a[i-1]<a[i])seq.back().emplace_back(a[i]);
        else seq.push_back({a[i]});
    }
    seq.back().emplace_back(2*n+1);
    for(int i=1;i<seq.size();i++)if(seq[i].size()==1)return void(cout << 0 << "\n");
    int l=1,r=n;
    for(int i=1;i<seq.size();i++)l=max(l,seq[i-1].back()-seq[i][0]);
    for(int i=1;i<seq.size();i++){
        int gap=0;
        for(int j=1;j<seq[i].size();j++)gap=max(gap,seq[i][j]-seq[i][j-1]);
        r=min(r,gap);
    }
    if(l>r)cout << 0 << "\n";
    else cout << 1ll*(l+r)*(r-l+1)/2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}