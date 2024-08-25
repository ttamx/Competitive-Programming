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
    int n,q;
    cin >> n >> q;
    vector<int> col(n);
    vector<vector<int>> a(16);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(auto x:s){
            if(x=='R')col[i]|=1;
            if(x=='G')col[i]|=2;
            if(x=='B')col[i]|=4;
            if(x=='Y')col[i]|=8;
        }
        a[col[i]].emplace_back(i);
    }
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        int ans=INF;
        vector<int> ord{1,2,4,8};
        do{
            if(!(ord[0]&col[u]))continue;
            map<int,int> dp;
            dp[u]=0;
            for(int i=0;i<4;i++){
                if(col[v]&ord[i]){
                    auto it=dp.lower_bound(v);
                    if(it!=dp.end()){
                        ans=min(ans,it->second+abs(v-it->first));
                    }
                    if(it!=dp.begin()){
                        it--;
                        ans=min(ans,it->second+abs(v-it->first));
                    }
                    break;
                }
                if(i<3){
                    map<int,int> ndp;
                    auto update=[&](int x,int v){
                        if(ndp.count(x)){
                            ndp[x]=min(ndp[x],v);
                        }else{
                            ndp[x]=v;
                        }
                    };
                    auto &b=a[ord[i]|ord[i+1]];
                    for(auto [x,y]:dp){
                        auto it=lower_bound(b.begin(),b.end(),x);
                        if(it!=b.end()){
                            update(*it,y+abs(x-*it));
                        }
                        if(it!=b.begin()){
                            it--;
                            update(*it,y+abs(x-*it));
                        }
                    }
                    swap(dp,ndp);
                }
            }
        }while(next_permutation(ord.begin(),ord.end()));
        cout << (ans<INF?ans:-1) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}