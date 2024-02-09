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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    ll ans=INF;
    vector<vl> ver(n,vl(m)),hor(n,vl(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ver[i][j]=hor[i][j]=a[i][j]=='x'?INF:(a[i][j]=='o'?0:1);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i)ver[i][j]+=ver[i-1][j];
            if(j)hor[i][j]+=hor[i][j-1];
            if(i>=k-1){
                ans=min(ans,ver[i][j]-(i>=k?ver[i-k][j]:0));
            }
            if(j>=k-1){
                ans=min(ans,hor[i][j]-(j>=k?hor[i][j-k]:0));
            }
        }
    }
    cout << (ans<INF?ans:-1) << "\n";
}