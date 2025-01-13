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

const int N=2e6+5;

bool sheet[5][5];
bool _vis[N];

int _n,_m;

bool &vis(int i,int j){
    return _vis[i*_m+j];
}

void runcase(){
    int n,m;
    cin >> n >> m;
    _n=n,_m=m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            vis(i,j)=false;
        }
    }
    vector<pair<int,int>> comp;
    function<void(int,int)> dfs=[&](int i,int j){
        queue<pair<int,int>> q;
        auto push=[&](int i,int j){
            if(i<0||j<0||i>=n||j>=m||vis(i,j))return;
            comp.emplace_back(i,j);
            vis(i,j)=true;
            q.emplace(i,j);
        };
        push(i,j);
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            push(i-1,j);
            push(i,j-1);
            push(i,j+1);
            push(i+1,j);
        }
    };
    int res=0;
    function<void(int,int,int)> dfs2=[&](int i,int j,int p){
        queue<pair<int,int>> q;
        auto push=[&](int i,int j){
            if(i<0||j<0||i>=n||j>=m||vis(i,j))return;
            vis(i,j)=true;
            q.emplace(i,j);
            if((i+j)%2==p){
                a[i][j]='S';
                res++;
            }
        };
        push(i,j);
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            push(i-1,j);
            push(i,j-1);
            push(i,j+1);
            push(i+1,j);
        }
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                vis(i,j)=true;
            }
        }
    }
    auto check=[&](int i,int j){
        return (i>=0&&i<n&&j>=0&&j<m&&a[i][j]=='S');
    };
    auto work=[&](int oi,int oj){
        res=0;
        for(auto [i,j]:comp){
            a[i][j]='#';
            vis(i,j)=false;
        }
        for(auto [i,j]:comp){
            if(sheet[(i+oi)%5][(j+oj)%5]){
                a[i][j]='S';
                res++;
            }
        }
        for(auto [i,j]:comp){
            if(a[i][j]=='S'||check(i-1,j)||check(i,j-1)||check(i,j+1)||check(i+1,j)){
                vis(i,j)=true;
            }
        }
        for(auto [i,j]:comp){
            if(!vis(i,j)){
                dfs2(i,j,(i+j)%2);
            }
        }
        return res;
    };
    auto solve=[&](){
        pair<int,int> best(INF,0);
        for(int i=0;i<5;i++){
            best=min(best,{work(i,0),i});
        }
        work(get<1>(best),0);
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'&&!vis(i,j)){
                dfs(i,j);
                sort(comp.begin(),comp.end());
                solve();
                comp.clear();
            }
        }
    }
    for(auto x:a){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    sheet[0][2]=true;
    sheet[1][0]=true;
    sheet[2][3]=true;
    sheet[3][1]=true;
    sheet[4][4]=true;
    int t(1);
    cin >> t;
    while(t--)runcase();
}