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
    vector<vi> a(7,vi(7));
    vector<pair<int,int>> b,c;
    for(int i=1;i<6;i++)for(int j=1;j<6;j++)if((i+j)%2==0)b.emplace_back(i,j);
    for(int i=1;i<6;i++)for(int j=1;j<6;j++)if((i+j)%2==1)c.emplace_back(i,j);
    for(auto &v:a){
        for(auto &x:v){
            char c;
            cin >> c;
            x=c=='B';
        }
    }
    int ans=0;
    auto check=[&](int p){
        for(int i=1;i<6;i++){
            for(int j=1;j<6;j++)if((i+j)%2==p){
                if(a[i][j]+a[i-1][j-1]+a[i-1][j+1]+a[i+1][j-1]+a[i+1][j+1]==5)return false;
            }
        }
        return true;
    };
    {
        int res=4;
        for(int i=0;i<1<<sz(b);i++){
            if(__builtin_popcount(i)>=4)continue;
            int tmp=0;
            for(int j=0;j<sz(b);j++)if(i>>j&1){
                auto [x,y]=b[j];
                a[x][y]^=1;
                tmp++;
            }
            if(check(0))res=min(res,tmp);
            for(int j=0;j<sz(b);j++)if(i>>j&1){
                auto [x,y]=b[j];
                a[x][y]^=1;
            }
        }
        ans+=res;
    }
    {
        int res=4;
        for(int i=0;i<1<<sz(c);i++){
            if(__builtin_popcount(i)>=4)continue;
            int tmp=0;
            for(int j=0;j<sz(c);j++)if(i>>j&1){
                auto [x,y]=c[j];
                a[x][y]^=1;
                tmp++;
            }
            if(check(1))res=min(res,tmp);
            for(int j=0;j<sz(c);j++)if(i>>j&1){
                auto [x,y]=c[j];
                a[x][y]^=1;
            }
        }
        ans+=res;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}