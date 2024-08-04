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
    int n,m;
    cin >> n >> m;
    vector<int> c(n),a(m);
    for(auto &x:c){
        cin >> x;
        x--;
    }
    for(auto &x:a)cin >> x;
    if(m==1)return void(cout << a[0] << "\n");
    int h1=m/2,h2=m-h1;
    vector<int> add(h1);
    vector<vector<bool>> con(m,vector<bool>(m));
    for(int i=1;i<n;i++){
        int u=c[i-1],v=c[i];
        if(u>v)swap(u,v);
        con[u][v]=true;
        if(u<h1&&v>=h1){
            add[u]|=1<<(v-h1);
        }
    }
    vector<int> dp1(1<<h1),dp2(1<<h2);
    for(int i=0;i<1<<h1;i++){
        for(int j=0;j<h1;j++){
            if(i>>j&1){
                dp1[i]+=a[j];
            }
        }
        for(int j=0;j<h1;j++){
            if(!(i>>j&1)){
                for(int k=j;k<h1;k++){
                    if(!(i>>k&1)){
                        if(con[j][k]){
                            dp1[i]=INF;
                            break;
                        }
                    }
                }
                if(dp1[i]==INF)break;
            }
        }
    }
    for(int i=0;i<1<<h2;i++){
        for(int j=0;j<h2;j++){
            if(i>>j&1){
                dp2[i]+=a[j+h1];
            }
        }
        for(int j=0;j<h2;j++){
            if(!(i>>j&1)){
                for(int k=j;k<h2;k++){
                    if(!(i>>k&1)){
                        if(con[j+h1][k+h1]){
                            dp2[i]=INF;
                            break;
                        }
                    }
                }
                if(dp2[i]==INF)break;
            }
        }
    }
    for(int i=(1<<h2)-1;i>0;i--){
        for(int j=0;j<h2;j++){
            if(i>>j&1){
                int mask=i^(1<<j);
                dp2[mask]=min(dp2[mask],dp2[i]);
            }
        }
    }
    int ans=INF;
    for(int i=0;i<1<<h1;i++){
        if(c[0]<h1&&!(i>>c[0]&1))continue;
        if(c[n-1]<h1&&!(i>>c[n-1]&1))continue;
        int mask=0;
        if(c[0]>=h1)mask|=1<<(c[0]-h1);
        if(c[n-1]>=h1)mask|=1<<(c[n-1]-h1);
        for(int j=0;j<h1;j++){
            if(!(i>>j&1)){
                mask|=add[j];
            }
        }
        ans=min(ans,dp1[i]+dp2[mask]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}