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
    auto ask=[&](int a,int b){
        assert(a<b);
        cout << "? " << a << " " << b << endl;
        int res=0;
        cin >> res;
        if(res==a*b)return 2;
        if(res==a*(b+1))return 1;
        if(res==(a+1)*(b+1))return 0;
        assert(false);
        return -1;
    };
    int l=2,r=999;
    while(r-l+1>=3){
        int sz=r-l+1;
        int s=sz/3;
        int x=ask(l+s,l+s*2);
        if(x==0){
            r=l+s;
        }else if(x==1){
            r=l+2*s;
            l=l+s+1;
        }else if(x==2){
            l=l+2*s+1;
        }
    }
    if(l<r){
        if(ask(l-1,l)==1){
            r=l;
        }else{
            l=r;
        }
    }
    cout << "! " << l << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}