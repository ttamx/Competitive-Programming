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
    vi a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vi ans(n+2,INF);
    for(int t=0;t<2;t++){
        vl qs(n+2);
        vi pp(n+2);
        int p=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=a[p])p=i;
            pp[i]=p;
            qs[i]=a[i]+qs[i-1];
            int l=0,r=i-1;
            while(l<r){
                int m=(l+r+1)/2;
                if(qs[i-1]-(m?qs[m-1]:0)>a[i]){
                    l=m;
                }else{
                    r=m-1;
                }
            }
            if(l<i-1&&l>=pp[i-1])l=pp[i-1]-1;
            if(l)ans[i]=min(ans[i],i-l);
        }
        reverse(all(a));
        reverse(all(ans));
    }
    for(int i=1;i<=n;i++)cout << (ans[i]==INF?-1:ans[i]) << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}