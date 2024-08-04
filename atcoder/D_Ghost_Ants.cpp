#include<bits/stdc++.h>

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
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,t;
    cin >> n >> t;
    string s;
    cin >> s;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=s[i]-'0';
    }
    sort(a.begin(),a.end());
    deque<int> dq;
    ll ans=0;
    for(auto [x,d]:a){
        if(d){
            dq.emplace_back(x);
        }else{
            while(!dq.empty()&&dq.front()+t<x-t)dq.pop_front();
            ans+=dq.size();
        }
    }
    cout << ans;
}