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
    vi a(n);
    for(auto &x:a)cin >> x;
    for(int t=0;t<2000;t++){
        for(int i=0;i<n;i++){
            int j=(i+1)%n;
            a[j]=max(0,a[j]-a[i]);
        }
    }
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        a[j]=max(0,a[j]-a[i]);
        if(a[j]==0)break;
    }
    vi ans;
    for(int i=0;i<n;i++){
        int x=a[i],y=a[(i+1)%n],z=a[(i+2)%n];
        if(a[(i+n-1)%n]==0&&x>0){
            ans.emplace_back(i);
            if(y>0&&z>0){
                int d=(y-1)/x+1;
                int st=max(y-x,y%x),ed=y%x;
                ll sum=1LL*(st+ed)*((st-ed)/x+1)/2;
                if(sum<z)ans.emplace_back((i+2)%n);
                i+=2;
            }else{
                i++;
            }
        }
    }
    sort(all(ans));
    ans.erase(unique(all(ans)),ans.end());
    cout << sz(ans) << "\n";
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}