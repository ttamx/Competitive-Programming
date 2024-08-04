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
    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s;
    vector<int> cnt(n);
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        cnt[x-1]++;
    }
    cin >> t;
    deque<char> a;
    for(auto x:t)a.emplace_back(x);
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++)if(cnt[i]){
        cnt[i]--;
        s[i]=a.front();
        a.pop_front();
        while(cnt[i]--)a.pop_back();
    }
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}