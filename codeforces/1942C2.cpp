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
    int n,x,y;
    cin >> n >> x >> y;
    vi a(x);
    for(auto &x:a)cin >> x;
    sort(all(a));
    a.emplace_back(a[0]+n);
    int ans=x+y-2,cnt=0;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=1;i<=x;i++){
        int gap=a[i]-a[i-1];
        cnt+=(gap-1)/2;
        if(gap%2==0){
            pq.emplace(gap/2-1);
        }
    }
    while(!pq.empty()&&y>=pq.top()){
        y-=pq.top();
        ans+=pq.top()+1;
        cnt-=pq.top();
        pq.pop();
    }
    ans+=min(y,cnt);
    if(y>cnt)ans-=y-cnt;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}