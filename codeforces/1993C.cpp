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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    int mx=a.back()-2*k;
    for(auto &x:a){
        if(x>=mx){
            break;
        }
        int t=(mx-x-1)/(2*k)+1;
        x+=2*k*t;
    }

    sort(a.begin(),a.end());
    mx=a.back();
    for(auto x:a){
        if(mx-x+1<=k){
            cout << mx << "\n";
            return;
        }
        mx=x+2*k;
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}