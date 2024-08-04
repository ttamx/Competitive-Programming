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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int cur=0,mul=1;
    vector<int> ans;
    for(int i=0;i<n;i++){
        int val=mul*a[i];
        if(mul==-1){
            if(abs(cur)<=abs(cur+val)){
                mul=1;
                val=-val;
                ans.emplace_back(i);
            }
        }
        cur+=val;
        mul=-mul;
    }
    if(cur!=0)cout << -1 << "\n";
    else{
        ans.emplace_back(n);
        cout << ans.size() << "\n";
        int pre=1;
        for(auto x:ans){
            cout << pre << " " << x << "\n";
            pre=x+1;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}