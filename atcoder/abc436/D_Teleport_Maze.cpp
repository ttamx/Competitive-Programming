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

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<pair<int,int>>> pos(26);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(isalpha(a[i][j])){
                pos[a[i][j]-'a'].emplace_back(i,j);
            }
        }
    }
    queue<pair<int,int>> q;
    vector<vector<int>> d(n,vector<int>(m,-1));
    d[0][0]=0;
    q.emplace(0,0);
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        if(i==n-1&&j==m-1){
            cout << d[i][j] << "\n";
            return;
        }
        if(isalpha(a[i][j])){
            for(auto [ii,jj]:pos[a[i][j]-'a']){
                if(d[ii][jj]==-1){
                    d[ii][jj]=d[i][j]+1;
                    q.emplace(ii,jj);
                }
            }
            pos[a[i][j]-'a'].clear();
        }
        for(int k=0;k<4;k++){
            int ii=i+dx[k],jj=j+dy[k];
            if(ii>=0&&ii<n&&jj>=0&&jj<m&&a[ii][jj]!='#'&&d[ii][jj]==-1){
                d[ii][jj]=d[i][j]+1;
                q.emplace(ii,jj);
            }
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}