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
    int n,q;
    cin >> n >> q;
    int nn=2,b=0;
    while(nn<n)nn<<=1,b++;
    vector<bool> seen(nn);
    vector<bool> mx(nn),mn(nn);
    function<void(int)> addmx=[&](int x){
        if(mx[x])return;
        mx[x]=true;
        for(int i=0;i<=b;i++){
            if(x>>i&1){
                addmx(x^(1<<i));
            }
        }
    };
    function<void(int)> addmn=[&](int x){
        if(mn[x])return;
        mn[x]=true;
        for(int i=0;i<=b;i++){
            if(x>>i&1){
                addmn(x^(1<<i));
            }
        }
    };
    int ans=0,cnt=0;
    for(int i=0;i<q;i++){
        int v;
        cin >> v;
        v=(v+ans)%n;
        if(!seen[v]){
            seen[v]=true;
            int cur=0;
            for(int j=b;j>=0;j--){
                if(v>>j&1){
                    if(mn[cur|(1<<j)]){
                        cur|=1<<j;
                    }
                }
            }
            ans=max(ans,cur);
            cur=0;
            for(int j=b;j>=0;j--){
                if(v>>j&1^1){
                    if(mx[cur|(1<<j)]){
                        cur|=1<<j;
                    }
                }
            }
            addmx(v);
            addmn(v^(nn-1));
            ans=max(ans,cur);
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}