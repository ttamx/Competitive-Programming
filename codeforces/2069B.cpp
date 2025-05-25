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
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<int> val(n*m+1);
    vector<vector<bool>> vis(n,vector<bool>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(vis[i][j])continue;
            queue<pair<int,int>> q;
            q.emplace(i,j);
            int cnt=0;
            auto go=[&](int x,int y){
                if(x>=0&&x<n&&y>=0&&y<m&&!vis[x][y]&&a[i][j]==a[x][y]){
                    vis[x][y]=true;
                    q.emplace(x,y);
                }
            };
            while(!q.empty()){
                auto [x,y]=q.front();
                q.pop();
                cnt++;
                go(i-1,j);
                go(i+1,j);
                go(i,j-1);
                go(i,j+1);
            }
            val[a[i][j]]=max(val[a[i][j]],cnt>1?2:1);
        }
    }
    cout << accumulate(val.begin(),val.end(),0)-*max_element(val.begin(),val.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}