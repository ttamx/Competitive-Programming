#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    int q;
    cin >> q;
    int cnt[35]={};
    while(q--){
        ll t,x;
        cin >> t >> x;
        if(t==1){
            cnt[x]++;
            if(x<=30&&cnt[x]>2){
                cnt[x]-=2;
                cnt[x+1]++;
            }
        }else{
            for(int i=30;i>=0;i--){
                for(int j=0;j<cnt[i];j++){
                    if(x>=(1<<i))x-=1<<i;
                }
            }
            cout << (x==0?"YES":"NO") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}