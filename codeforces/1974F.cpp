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
    int a,b,n,m;
    cin >> a >> b >> n >> m;
    int lx=1,rx=a,ly=1,ry=b;
    deque<pii> dx,dy;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        dx.emplace_back(x,i);
        dy.emplace_back(y,i);
    }
    sort(all(dx));
    sort(all(dy));
    vi ans(2),used(n);
    int t=0;
    while(m--){
        char c;
        int k;
        cin >> c >> k;
        if(c=='U')lx+=k;
        if(c=='D')rx-=k;
        if(c=='L')ly+=k;
        if(c=='R')ry-=k;
        while(!dx.empty()&&dx.front().first<lx){
            auto [x,i]=dx.front();
            dx.pop_front();
            if(used[i])continue;
            used[i]=true;
            ans[t]++;
        }
        while(!dx.empty()&&dx.back().first>rx){
            auto [x,i]=dx.back();
            dx.pop_back();
            if(used[i])continue;
            used[i]=true;
            ans[t]++;
        }
        while(!dy.empty()&&dy.front().first<ly){
            auto [x,i]=dy.front();
            dy.pop_front();
            if(used[i])continue;
            used[i]=true;
            ans[t]++;
        }
        while(!dy.empty()&&dy.back().first>ry){
            auto [x,i]=dy.back();
            dy.pop_back();
            if(used[i])continue;
            used[i]=true;
            ans[t]++;
        }
        t^=1;
    }
    cout << ans[0] << " " << ans[1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}