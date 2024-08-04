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
    auto ask=[&](int x,int y){
        cout << "? " << x << " " << y << endl;
        char c;
        cin >> c;
        return c=='y';
    };
    int l=0,r=1,d=1;
    while(ask(l,r)){
        l=r;
        r+=d;
        d*=2;
    }
    int lo=l+1,hi=r;
    while(lo<hi){
        int md=(lo+hi)/2;
        if(ask(l,md))lo=md+1;
        else hi=md;
    }
    cout << "! " << lo << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        string s;
        cin >> s;
        if(s=="end")break;
        runcase();
    }
}