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
    ll a,b,r;
    cin >> a >> b >> r;
    bool ok=false;
    ll sum=0;
    for(int i=60;i>=0;i--){
        ll x=a>>i&1;
        ll y=b>>i&1;
        if(!ok&&(r>>i&1)==0){
            sum+=(x<<i)-(y<<i);
        }else{
            if(x^y){
                if(x){
                    if(sum<=0){
                        sum+=1LL<<i;
                        ok=true;
                    }else{
                        sum-=1LL<<i;
                    }
                }else{
                    if(sum>=0){
                        sum-=1LL<<i;
                        ok=true;
                    }else{
                        sum+=1LL<<i;
                    }
                }
            }else{
                ok=true;
            }
        }
    }
    cout << abs(sum) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}