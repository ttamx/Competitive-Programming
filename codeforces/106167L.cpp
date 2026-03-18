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

int mp[256];

void runcase(){
    int n,m;
    cin >> n >> m;
    mp['W']=1;
    mp['A']=2;
    mp['L']=3;
    mp['D']=4;
    mp['O']=5;
    vector<vector<int>> a(n);
    for(auto &v:a){
        string s;
        cin >> s;
        for(auto x:s){
            v.emplace_back(mp[x]);
        }
    }
    if(n>m){
        vector<vector<int>> b(m,vector<int>(n));
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)b[j][i]=a[i][j];
        swap(n,m);
        a=move(b);
    }
    vector<vector<array<int,5>>> f(m,vector<array<int,5>>(n+1,array<int,5>{}));
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++){
            for(int k=0;k<5;k++){
                f[j][i+1][k]=f[j][i][k]+(a[i][j]==k+1);
            }
        }
    }
    int ans=n*m+1;
    for(int l=0;l<n;l++){
        for(int r=l;r<n;r++){
            array<int,5> c{};
            for(int i=0,p=0;i<m;i++){
                while(p<m&&*min_element(c.begin(),c.end())==0){
                    for(int k=0;k<5;k++){
                        c[k]+=f[p][r+1][k]-f[p][l][k];
                        assert(f[p][r+1][k]-f[p][l][k]>=0);
                    }
                    p++;
                }
                if(*min_element(c.begin(),c.end())>0){
                    ans=min(ans,(r-l+1)*(p-i));
                }
                for(int k=0;k<5;k++){
                    c[k]-=f[i][r+1][k]-f[i][l][k];
                    assert(f[i][r+1][k]-f[i][l][k]>=0);
                }
            }
        }
    }
    if(ans>n*m)cout << "impossible\n";
    else cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}