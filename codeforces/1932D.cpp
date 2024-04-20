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
    string t;
    cin >> t;
    map<string,vector<string>> vec;
    for(int i=0;i<2*n;i++){
        char x,s;
        cin >> x >> s;
        vec[string(1,s)].emplace_back(string(1,x));
    }
    vector<string> ans,rem;
    for(auto &[x,y]:vec){
        sort(rall(y));
        if(x!=t){
            while(sz(y)>1){
                ans.emplace_back(y.back()+x);
                y.pop_back();
                ans.emplace_back(y.back()+x);
                y.pop_back();
            }
            if(!y.empty()){
                rem.emplace_back(y.back()+x);
                y.pop_back();
            }
        }
    }
    while(!rem.empty()){
        if(vec[t].empty())return void(cout << "IMPOSSIBLE\n");
        ans.emplace_back(rem.back());
        rem.pop_back();
        ans.emplace_back(vec[t].back()+t);
        vec[t].pop_back();
    }
    while(sz(vec[t])>1){
        ans.emplace_back(vec[t].back()+t);
        vec[t].pop_back();
        ans.emplace_back(vec[t].back()+t);
        vec[t].pop_back();
    }
    for(int i=0;i<n;i++){
        cout << ans[i*2] << " " << ans[i*2+1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}