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
    priority_queue<pii> pq;
    for(int i=0;i<n;i++)if(a[i]!=-1)pq.emplace(a[i],i);
    if(pq.empty())pq.emplace(1,0);
    while(!pq.empty()){
        auto [x,i]=pq.top();
        pq.pop();
        if(x==1){
            if(i>0){
                if(a[i-1]==-1){
                    a[i-1]=2;
                    pq.emplace(2,i-1);
                }else if(a[i-1]/2!=1)return void(cout << "-1\n");
            }
            if(i+1<n){
                if(a[i+1]==-1){
                    a[i+1]=2;
                    pq.emplace(2,i+1);
                }else if(a[i+1]/2!=1)return void(cout << "-1\n");
            }
        }else{
            int v=x/2;
            if(i>0){
                if(a[i-1]==-1){
                    a[i-1]=v;
                    pq.emplace(v,i-1);
                }else if(a[i-1]!=v&&a[i-1]/2!=x)return void(cout << "-1\n");
            }
            if(i+1<n){
                if(a[i+1]==-1){
                    a[i+1]=v;
                    pq.emplace(v,i+1);
                }else if(a[i+1]!=v&&a[i+1]/2!=x)return void(cout << "-1\n");
            }
        }
    }
    for(auto x:a)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}