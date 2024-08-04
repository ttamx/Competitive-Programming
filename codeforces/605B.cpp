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
    vector<pair<int,int>> a(m);
    for(auto &[w,t]:a)cin >> w >> t;
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i].first<a[j].first||(a[i].first==a[j].first&&a[i].second>a[j].second);
    });
    int u=3,v=2,x=1;
    vector<pair<int,int>> ans(m);
    for(auto i:ord){
        if(a[i].second){
            x++;
            ans[i]={1,x};
        }else{
            if(u>x)return void(cout << "-1\n");
            ans[i]={v,u};
            v++;
            if(v==u){
                u++;
                v=2;
            }
        }
    }
    for(auto [u,v]:ans)cout << u << " " << v << "\n";
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}