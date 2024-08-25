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
    string s;
    cin >> n >> s;
    vector<int> cnt(26);
    for(auto x:s){
        cnt[x-'a']++;
    }
    vector<pair<int,int>> a;
    for(int i=0;i<26;i++){
        a.emplace_back(cnt[i],i);
    }
    sort(a.rbegin(),a.rend());
    string ans(n,'.');
    int idx=0;
    for(auto [c,x]:a){
        for(int i=0;i<c;i++){
            ans[idx]=char('a'+x);
            idx+=2;
            if(idx>=n)idx=1;
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