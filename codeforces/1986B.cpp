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
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &x:a)for(auto &y:x)cin >> y;
    priority_queue<tuple<int,int,int>> pq;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)pq.push({a[i][j],i,j});
    while(!pq.empty()){
        auto [v,i,j]=pq.top();
        pq.pop();
        int x=-1;
        if(i>0)x=max(x,a[i-1][j]);
        if(i<n-1)x=max(x,a[i+1][j]);
        if(j>0)x=max(x,a[i][j-1]);
        if(j<m-1)x=max(x,a[i][j+1]);
        if(x!=-1&&x<a[i][j])a[i][j]=x;
    }
    for(auto &x:a){
        for(auto &y:x)cout << y << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}