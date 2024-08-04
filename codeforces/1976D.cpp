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
    string s;
    cin >> s;
    int n=s.size();
    vector<deque<int>> dq(n/2+1);
    vector<pair<int,int>> st;
    int cur=0;
    dq[0].emplace_back(0);
    st.emplace_back(0,0);
    ll ans=0;
    for(int i=1;i<=n;i++){
        cur+=(s[i-1]=='('?1:-1);
        while(!st.empty()&&st.back().second<cur){
            st.pop_back();
        }
        st.emplace_back(i,cur);
        auto query=[&](int x){
            return lower_bound(st.begin(),st.end(),make_pair(x,0))->second;
        };
        int sz=1;
        while(!dq[cur].empty()&&query(dq[cur].front())>cur*2){
            dq[cur].pop_front();
        }
        ans+=dq[cur].size();
        dq[cur].emplace_back(i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}