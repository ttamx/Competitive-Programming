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
    int a,b;
    ll c;
    cin >> a >> b >> c;
    ll x=0,y=0;
    for(int i=0;i<60;i++){
        if(c>>i&1){
            if(a>b){
                a--;
                x|=1LL<<i;
            }else{
                if(b==0)cout << -1,exit(0);
                b--;
                y|=1LL<<i;
            }
        }
    }
    if(a!=b)cout << -1,exit(0);
    for(int i=0;i<60&&a>0;i++){
        if(((x|y)>>i&1)==0){
            a--;
            x|=1LL<<i;
            y|=1LL<<i;
        }
    }
    if(a>0)cout << -1;
    else cout << x << " " << y;
}