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
    int n,m,d;
    cin >> n >> m >> d;
    vector<int> up,dn,le,ri;
    for(int i=0;i<d;i++){
        int x,y;
        cin >> x >> y;
        if(x<=n/2){
            up.emplace_back(n/2-x+1);
        }else{
            dn.emplace_back(x-n/2);
        }
        if(y<=m/2){
            le.emplace_back(m/2-y+1);
        }else{
            ri.emplace_back(y-m/2);
        }
    }
    sort(up.rbegin(),up.rend());
    sort(dn.rbegin(),dn.rend());
    sort(le.rbegin(),le.rend());
    sort(ri.rbegin(),ri.rend());
    ll ans=0;
    while(up.size()>dn.size()){
        ans+=up.back();
        up.pop_back();
        dn.emplace_back(0);
    }
    while(dn.size()>up.size()){
        ans+=dn.back();
        dn.pop_back();
        up.emplace_back(0);
    }
    while(le.size()>ri.size()){
        ans+=le.back();
        le.pop_back();
        ri.emplace_back(0);
    }
    while(ri.size()>le.size()){
        ans+=ri.back();
        ri.pop_back();
        le.emplace_back(0);
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}