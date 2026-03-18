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
    priority_queue<pair<int,int>> row,col;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        row.emplace(x,i);
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        col.emplace(x,i);
    }
    queue<pair<int,int>> any;
    vector<queue<int>> p_row(n),p_col(m);
    vector<vector<int>> cnt(n,vector<int>(m));
    vector<vector<int>> ans(n,vector<int>(m));
    auto upd_row=[&](int i){
        for(int j=0;j<m;j++){
            cnt[i][j]++;
            if(cnt[i][j]==2){
                any.emplace(i,j);
            }else if(cnt[i][j]==1){
                p_col[j].emplace(i);
            }
        }
    };
    auto upd_col=[&](int j){
        for(int i=0;i<n;i++){
            cnt[i][j]++;
            if(cnt[i][j]==2){
                any.emplace(i,j);
            }else if(cnt[i][j]==1){
                p_row[i].emplace(j);
            }
        }
    };
    for(int v=n*m;v>=1;v--){
        int i=-1,j=-1;
        if(!row.empty()&&row.top().first==v){
            i=row.top().second;
            row.pop();
        }
        if(!col.empty()&&col.top().first==v){
            j=col.top().second;
            col.pop();
        }
        if(i==-1&&j==-1){
            if(any.empty()){
                cout << "No\n";
                return;
            }
            tie(i,j)=any.front();
            any.pop();
            ans[i][j]=v;
            cnt[i][j]=-INF;
        }else if(j==-1){
            while(!p_row[i].empty()&&cnt[i][p_row[i].front()]!=1){
                p_row[i].pop();
            }
            if(p_row[i].empty()){
                cout << "No\n";
                return;
            }
            j=p_row[i].front();
            p_row[i].pop();
            ans[i][j]=v;
            cnt[i][j]=-INF;
            upd_row(i);
        }else if(i==-1){
            while(!p_col[j].empty()&&cnt[p_col[j].front()][j]!=1){
                p_col[j].pop();
            }
            if(p_col[j].empty()){
                cout << "No\n";
                return;
            }
            i=p_col[j].front();
            p_col[j].pop();
            ans[i][j]=v;
            cnt[i][j]=-INF;
            upd_col(j);
        }else{
            ans[i][j]=v;
            cnt[i][j]=-INF;
            upd_row(i);
            upd_col(j);
        }
    }
    cout << "Yes\n";
    for(auto &v:ans){
        for(auto x:v){
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}