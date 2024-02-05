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
    auto ask=[&](int l,int r){
        cout << "? " << l << " " << r << endl;
        int res=0;
        for(int i=0;i<r-l+1;i++){
            int x;
            cin >> x;
            res^=l<=x&&x<=r;
        }
        return res;
    };
    int l=1,r=n;
    while(l<r){
        int sz=(r-l+1)/2;
        if(sz%2==0)sz++;
        int m=l+sz-1;
        if(ask(l,m))r=m;
        else l=m+1;
    }
    cout << "! " << l << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}