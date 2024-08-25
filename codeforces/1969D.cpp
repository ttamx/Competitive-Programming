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
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return b[i]>b[j]||(b[i]==b[j]&&a[i]<a[j]);
    });
    ll sum=0,cur=0,ans=0;
    for(int i=0;i<n;i++)sum+=max(b[i]-a[i],0);
    priority_queue<int> pq;
    for(auto i:ord){
        if(pq.size()==k){
            ans=max(ans,sum+cur);
        }
        cur-=a[i];
        pq.emplace(a[i]);
        if(pq.size()>k){
            cur+=pq.top();
            pq.pop();
        }
        sum-=max(b[i]-a[i],0);
    }
    ans=max(ans,sum+cur);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}