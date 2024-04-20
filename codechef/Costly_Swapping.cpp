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
    ll c,s,m;
    cin >> n >> c >> s >> m;
    vl a(n);
    for(auto &x:a)cin >> x;
    ll ans=n*c;
    ll sum=accumulate(all(a),0LL);
    multiset<ll> left,right,change,used;
    for(auto x:a)left.emplace(x);
    for(int i=n-1;i>=0;i--){
        while(sum<=m&&!left.empty()&&!right.empty()&&*left.begin()<*right.rbegin()){
            change.emplace(*left.begin());
            sum-=*left.begin();
            left.erase(left.begin());
            used.emplace(*right.rbegin());
            sum+=*right.rbegin();
            right.erase(prev(right.end()));
        }
        if(sum<=m)break;
        ans=min(ans,sz(change)*s+i*c);
        if(change.find(a[i])!=change.end()){
            change.erase(change.find(a[i]));
            right.emplace(*used.begin());
            sum-=*used.begin();
            used.erase(used.begin());
        }else{
            left.erase(left.find(a[i]));
            sum-=a[i];
        }
        right.emplace(a[i]);
        while(!used.empty()&&!right.empty()&&*right.rbegin()>*used.begin()){
            sum-=*used.begin();
            right.emplace(*used.begin());
            used.erase(used.begin());
            sum+=*right.rbegin();
            used.emplace(*right.rbegin());
            right.erase(prev(right.end()));
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}