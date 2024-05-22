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
    string s;
    cin >> n >> s;
    int dx=0,dy=0;
    vi xp,xn,yp,yn;
    for(int i=0;i<n;i++){
        char x=s[i];
        if(x=='N'){
            dx++;
            xp.emplace_back(i);
        }
        if(x=='S'){
            dx--;
            xn.emplace_back(i);
        }
        if(x=='E'){
            dy++;
            yp.emplace_back(i);
        }
        if(x=='W'){
            dy--;
            yn.emplace_back(i);
        }
    }
    if(dx%2||dy%2)return void(cout << "NO\n");
    dx/=2;
    dy/=2;
    char cx='R',cy='H';
    string p(n,' ');
    if(dx==0&&!xp.empty()){
        p[xp.back()]='H';
        xp.pop_back();
        dx--;
    }
    while(dx>0){
        p[xp.back()]='H';
        xp.pop_back();
        dx--;
    }
    while(dx<0){
        p[xn.back()]='H';
        xn.pop_back();
        dx++;
    }
    while(!xp.empty()){
        p[xp.back()]='R';
        xp.pop_back();
    }
    while(!xn.empty()){
        p[xn.back()]='R';
        xn.pop_back();
    }
    if(dy==0&&!yp.empty()){
        p[yp.back()]='R';
        yp.pop_back();
        dy--;
    }
    while(dy>0){
        p[yp.back()]='R';
        yp.pop_back();
        dy--;
    }
    while(dy<0){
        p[yn.back()]='R';
        yn.pop_back();
        dy++;
    }
    while(!yp.empty()){
        p[yp.back()]='H';
        yp.pop_back();
    }
    while(!yn.empty()){
        p[yn.back()]='H';
        yn.pop_back();
    }
    int ok=0;
    for(auto x:p){
        if(x=='H')ok|=1;
        if(x=='R')ok|=2;
    }
    cout << (ok==3?p:"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}