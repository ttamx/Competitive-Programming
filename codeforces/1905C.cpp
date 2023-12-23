#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    deque<int> dq;
    vector<bool> used(n);
    for(int i=0;i<n;i++){
        while(!dq.empty()&&s[dq.back()]<s[i])dq.pop_back();
        dq.emplace_back(i);
    }
    for(auto x:dq)used[x]=true;
    int p=1;
    while(p<sz(dq)&&s[dq[p]]==s[dq[0]])p++;
    int ans=sz(dq)-p;
    string t="";
    for(int i=0;i<n;i++){
        if(used[i]){
            t.push_back(s[dq.back()]);
            dq.pop_back();
        }else{
            t.push_back(s[i]);
        }
    }
    sort(all(s));
    cout << (s==t?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}