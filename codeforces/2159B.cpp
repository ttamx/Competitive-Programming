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
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    bool swapp=n<m;
    if(swapp){
        vector<string> b(m,string(n,'.'));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                b[j][i]=a[i][j];
            }
        }
        swap(a,b);
        swap(n,m);
    }
    vector<vector<int>> last(m,vector<int>(m,-1));
    vector<vector<vector<pair<int,int>>>> add(n,vector<vector<pair<int,int>>>(m));
    for(int i=0;i<n;i++){
        for(int l=0;l<m;l++){
            if(a[i][l]=='0')continue;
            for(int r=l+1;r<m;r++){
                if(a[i][r]=='0')continue;
                int p=last[l][r];
                if(p!=-1){
                    int area=(i-p+1)*(r-l+1);
                    for(int k=p;k<=i;k++){
                        add[k][l].emplace_back(area,r);
                    }
                }
                last[l][r]=i;
            }
        }
    }
    vector<vector<int>> ans(n,vector<int>(m));
    for(int i=0;i<n;i++){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(int j=0;j<m;j++){
            for(auto [v,k]:add[i][j]){
                pq.emplace(v,k);
            }
            while(!pq.empty()&&pq.top().second<j){
                pq.pop();
            }
            if(!pq.empty()){
                ans[i][j]=pq.top().first;
            }
        }
    }
    if(swapp){
        vector<vector<int>> ans2(m,vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans2[j][i]=ans[i][j];
            }
        }
        swap(ans,ans2);
        swap(n,m);
    }
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