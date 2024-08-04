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
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    int sum=0;
    for(int i=1;i<=n;i++)sum+=a[i];
    if(sum%n)return void(cout << "-1\n");
    int avg=sum/n;
    vector<tuple<int,int,int>> ans;
    auto work=[&](int i,int j,int x){
        a[i]-=i*x;
        a[j]+=i*x;
        ans.emplace_back(i,j,x);
    };
    for(int i=2;i<=n;i++){
        int x=(i-a[i]%i)%i;
        work(1,i,x);
        work(i,1,a[i]/i);
    }
    for(int i=2;i<=n;i++)work(1,i,avg);
    cout << ans.size() << "\n";
    for(auto [i,j,x]:ans)cout << i << " " << j << " " << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}