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
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    if(a[0].first>=k)return void(cout << "YES\n");
    if(a[0].first+a[0].second<k)return void(cout << "NO\n");
    int cur=k-a[0].second;
    vector<pair<int,int>> b;
    for(int i=1;i<n;i++){
        auto [x,y]=a[i];
        b.emplace_back(x+y,i);
    }
    sort(b.begin(),b.end());
    priority_queue<pair<int,int>> pq;
    auto work=[&](){
        while(!b.empty()&&b.back().first>=cur){
            auto [x,y]=a[b.back().second];
            b.pop_back();
            pq.emplace(y,-x);
        }
    };
    work();
    while(!pq.empty()){
        auto [y,x]=pq.top();
        pq.pop();
        x=-x;
        if(x>=cur)return void(cout << "YES\n");
        cur-=y;
        work();
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}