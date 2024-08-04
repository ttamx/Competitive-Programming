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
    auto pal=[&](const string &s){
        auto t=s;
        reverse(t.begin(),t.end());
        return t==s;
    };
    string s;
    cin >> s;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    int ans=0;
    map<string,bool> mp;
    do{
        string t="";
        for(auto x:ord)t.push_back(s[x]);
        if(mp[t])continue;
        mp[t]=true;
        int ok=1;
        for(int i=0;i+k<=n;i++){
            if(pal(t.substr(i,k)))ok=0;
        }
        ans+=ok;
    }while(next_permutation(ord.begin(),ord.end()));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}