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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,int>> ans;
    set<int> id;
    for(int i=0;i<n;i++)id.emplace(i);
    for(int i=n-1;i>=1;i--){
        map<int,int> mp;
        bool ok=false;
        for(auto j:id){
            int x=a[j]%i;
            if(mp.count(x)){
                ans.emplace_back(j,mp[x]);
                id.erase(j);
                ok=true;
                break;
            }else{
                mp[x]=j;
            }
        }
        assert(ok);
    }
    reverse(ans.begin(),ans.end());
    cout << "YES\n";
    for(auto [u,v]:ans)cout << u+1 << " " << v+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}