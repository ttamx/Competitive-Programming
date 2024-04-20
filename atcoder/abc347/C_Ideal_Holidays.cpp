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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,a,b;
    cin >> n >> a >> b;
    int w=a+b;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int d;
        cin >> d;
        mp[d%w]++;
    }
    deque<int> dq;
    for(auto [x,y]:mp)dq.emplace_back(x);
    int m=dq.size();
    for(int i=0;i<m;i++){
        if(dq.back()-dq.front()+1<=a)cout << "Yes",exit(0);
        dq.emplace_back(dq.front()+w);
        dq.pop_front();
    }
    cout << "No";
}