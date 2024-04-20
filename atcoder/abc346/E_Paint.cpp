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
    ll h,w;
    int m;
    cin >> h >> w >> m;
    vector<tuple<int,int,int>> qr(m);
    for(auto &[t,a,x]:qr)cin >> t >> a >> x,t--;
    map<int,bool> seen[2];
    map<int,ll> ans;
    reverse(all(qr));
    int c[2]={};
    ans[0]=h*w;
    for(auto [t,a,x]:qr){
        if(seen[t][a])continue;
        seen[t][a]=true;
        if(t){
            ans[x]+=h-c[0];
            ans[0]-=h-c[0];
        }else{
            ans[x]+=w-c[1];
            ans[0]-=w-c[1];
        }
        c[t]++;
    }
    for(auto it=ans.begin();it!=ans.end();){
        if(it->second==0)it=ans.erase(it);
        else it++;
    }
    cout << sz(ans) << "\n";
    for(auto [x,y]:ans)cout << x << " " << y << "\n";
}