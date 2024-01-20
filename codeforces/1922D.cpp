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
    vi a(n+2),b(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    set<int> s,d;
    for(int i=0;i<=n+1;i++)s.emplace(i);
    for(int i=1;i<=n;i++)if(a[i-1]+a[i+1]>b[i])d.emplace(i);
    for(int t=0;t<n;t++){
        cout << sz(d) << " \n"[t==n-1];
        vector<set<int>::iterator> upd;
        for(auto j:d){
            auto it=s.find(j);
            if(!upd.empty()&&upd.back()==it)upd.pop_back();
            it=s.erase(it);
            if(upd.empty()||upd.back()!=prev(it)){
                upd.emplace_back(prev(it));
            }
            upd.emplace_back(it);
        }
        d.clear();
        for(auto it:upd){
            if(it==s.begin()||next(it)==s.end())continue;
            if(a[*prev(it)]+a[*next(it)]>b[*it])d.emplace(*it);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}