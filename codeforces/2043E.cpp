#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    vector<vector<int>> b(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
        }
    }
    for(int bit=0;bit<30;bit++){
        auto aa=a,bb=b;
        for(auto &v:aa){
            for(auto &x:v){
                x=x>>bit&1;
            }
        }
        for(auto &v:bb){
            for(auto &x:v){
                x=x>>bit&1;
            }
        }
        int nn=n,mm=m;
        vector<bool> row(n),col(m);
        priority_queue<pair<int,int>> pqrow,pqcol;
        for(int i=0;i<n;i++){
            int cnt=0;
            for(int j=0;j<m;j++){
                if(bb[i][j]==0){
                    cnt++;
                }
            }
            pqrow.emplace(cnt,i);
        }
        for(int i=0;i<m;i++){
            int cnt=0;
            for(int j=0;j<n;j++){
                if(bb[j][i]==1){
                    cnt++;
                }
            }
            pqcol.emplace(cnt,i);
        }
        while(true){
            if(!pqrow.empty()&&pqrow.top().first==mm){
                row[pqrow.top().second]=true;
                pqrow.pop();
                nn--;
                continue;
            }
            if(!pqcol.empty()&&pqcol.top().first==nn){
                col[pqcol.top().second]=true;
                pqcol.pop();
                mm--;
                continue;
            }
            break;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!row[i]&&!col[j]&&aa[i][j]!=bb[i][j]){
                    cout << "No\n";
                    return;
                }
            }
        }
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}