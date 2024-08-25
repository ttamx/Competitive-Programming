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
    vector<ll> a(n+1),b(n+1);
    b[0]=-1,a[0]=INF;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
    }
    multiset<pair<ll,int>> ms;
    vector<ll> val(n+1,-1);
    for(int i=1;i<=n;i++){
        if(b[i]!=b[i-1]){
            ms.emplace(a[i],i);
            val[i]=a[i];
        }
    }
    set<int> pos;
    for(int i=0;i<=n;i++){
        pos.emplace(i);
    }
    vector<ll> ans(n+1);
    auto cur=a;
    while(!ms.empty()){
        auto [t,i]=*ms.begin();
        ms.erase(ms.begin());
        pos.erase(i);
        val[i]=-1;
        ans[i]=t;
        auto it=pos.lower_bound(i);
        if(it!=pos.end()&&it!=pos.begin()){
            int l=*prev(it),r=*it;
            if(val[r]!=-1){
                ms.erase(ms.find({val[r],r}));
                cur[r]=val[r]-t;
                val[r]=-1;
            }
            if(b[l]!=b[r]){
                val[r]=cur[r]+t;
                ms.emplace(val[r],r);
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans[i]=max(ans[i],ans[i-1]);
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}