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
    int n,k,w,h;
    cin >> n >> k >> w >> h;
    w*=2,h*=2;
    string s;
    cin >> s;
    int dx=0,dy=0;
    map<pair<int,int>,int> cnt;
    for(auto x:s){
        if(x=='L'){
            dx--;
        }
        if(x=='R'){
            dx++;
        }
        if(x=='U'){
            dy++;
        }
        if(x=='D'){
            dy--;
        }
        if(dx<0){
            dx+=w;
        }
        if(dx>=w){
            dx-=w;
        }
        if(dy<0){
            dy+=h;
        }
        if(dy>=h){
            dy-=h;
        }
        cnt[{dx,dy}]++;
    }
    int x=0,y=0;
    ll ans=0;
    for(int i=0;i<k;i++){
        ans+=cnt[{(w-x)%w,(h-y)%h}];
        x+=dx,y+=dy;
        if(x>=w){
            x-=w;
        }
        if(y>=h){
            y-=h;
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