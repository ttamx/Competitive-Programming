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
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int u=0,v=0,add=0,del=0;
    for(int i=0;i<n;i++){
        if(a[i]>0&&b[i]<1)u++;
        else if(b[i]>0&&a[i]<1)v++;
        else if(a[i]>0&&b[i]>0)add++;
        else if(a[i]<0&&b[i]<0)del++;
    }
    while(add--){
        if(u>v)swap(u,v);
        u++;
    }
    while(del--){
        if(u>v)swap(u,v);
        v--;
    }
    cout << min(u,v) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}