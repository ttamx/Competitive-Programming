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
    ll a,b,c,d;
    cin >> a >> b >> c >> d;
    ll x=abs(b-d);
    if((a+b)%2==0)a++;
    if((c+d)%2==0)c++;
    if(a<c){
        a+=x;
        cout << x+max(0ll,(c-a)/2) << "\n";
    }else if(a>c){
        a-=x;
        cout << x+max(0ll,(a-c)/2) << "\n";
    }else{
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}