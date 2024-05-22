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
    auto ask=[&](int l,int x){
        cout << "? " << l << " " << x << endl;
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](int x){
        cout << "! " << x << endl;
        int res;
        cin >> res;
        assert(res==1);
    };
    int mx=1;
    for(int i=2;i<=n;i++)if(ask(1,i*n)==n)mx=i;
    for(int i=n/k;i>=1;i--){
        int p=1;
        bool ok=true;
        int val=mx*i;
        for(int i=1;i<=k;i++){
            if(p>n){
                ok=false;
                break;
            }
            p=ask(p,val)+1;
        }
        if(!ok)continue;
        if(p==n+1)return answer(val);
    }
    answer(-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}