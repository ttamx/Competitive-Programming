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
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto check=[&](int i,int j,int d1,int d2){
        if(d1){
            if(d2){
                int l1=a[i],r1=b[i];
                int l2=a[j],r2=b[j];
                if(l1>r1)r1+=m;
                if(l2>r2)r2+=m;
                if(l1<=l2&&r2<=r1)return false;
                if(l2<=l1&&r1<=r2)return false;
                return true;
            }
        }
    };
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}