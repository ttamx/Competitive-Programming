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
    for(auto &x:a)cin >> x;
    vector<tuple<char,int,int,bool>> b;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(isalpha(a[i][j])){
                b.emplace_back(a[i][j],i,j,1);
            }
        }
    }
    vector<vector<int>> ver(n,vector<int>(m)),hor(n,vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ver[i][j]=hor[i][j]=(a[i][j]=='#');
            if(i>0)ver[i][j]+=ver[i-1][j];
            if(j>0)hor[i][j]+=hor[i][j-1];
        }
    }
    auto qver=[&](int i,int l,int r){
        if(l>r)swap(l,r);
        if(l<0||r>=n)return 1;
        return ver[r][i]-(l?ver[l-1][i]:0);
    };
    auto qhor=[&](int i,int l,int r){
        if(l>r)swap(l,r);
        if(l<0||r>=m)return 1;
        return hor[i][r]-(l?hor[i][l-1]:0);
    };
    int k;
    cin >> k;
    while(k--){
        char d;
        int s;
        cin >> d >> s;
        for(auto &[c,x,y,t]:b){
            if(!t)continue;
            if(d=='N'){
                if(qver(y,x-1,x-s))t=0;
                else x-=s;
            }
            if(d=='S'){
                if(qver(y,x+1,x+s))t=0;
                else x+=s;
            }
            if(d=='W'){
                if(qhor(x,y-1,y-s))t=0;
                else y-=s;
            }
            if(d=='E'){
                if(qhor(x,y+1,y+s))t=0;
                else y+=s;
            }
        }
    }
    string ans="";
    for(auto [c,x,y,t]:b)if(t)ans+=c;
    sort(ans.begin(),ans.end());
    if(ans.empty())ans="no solution";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}