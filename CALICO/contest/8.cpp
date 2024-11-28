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
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> qs(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='*')qs[i][j]++;
            if(j>0)qs[i][j]+=qs[i][j-1];
            if(i>0)qs[i][j]+=qs[i-1][j];
            if(i>0&&j>0)qs[i][j]-=qs[i-1][j-1];
            qs[i][j]+=(a[i][j]=='S');
        }
    }
    auto query=[&](int x1,int y1,int x2,int y2){
        if(x1>x2)swap(x1,x2);
        if(y1>y2)swap(y1,y2);
        int res=qs[x2][y2];
        if(x1>0)res-=qs[x1-1][y2];
        if(y1>0)res-=qs[x2][y1-1];
        if(x1>0&&y1>0)res+=qs[x1-1][y1-1];
        return res;
    };
    vector<vector<pair<int,int>>> no,ea,so,we;
    no=so=ea=we=vector<vector<pair<int,int>>>(n,vector<pair<int,int>>(m,{-1,-1}));
    for(int i=0;i<n;i++){
        int wall=0;
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                wall=j;
            }else{
                we[i][j]={i,max(wall+1,j-k)};
            }
        }
        wall=m-1;
        for(int j=m-1;j>=0;j--){
            if(a[i][j]=='#'){
                wall=j;
            }else{
                ea[i][j]={i,min(wall-1,j+k)};
            }
        }
    }
    for(int j=0;j<m;j++){
        int wall=0;
        for(int i=0;i<n;i++){
            if(a[i][j]=='#'){
                wall=i;
            }else{
                no[i][j]={max(wall+1,i-k),j};
            }
        }
        wall=n-1;
        for(int i=n-1;i>=0;i--){
            if(a[i][j]=='#'){
                wall=i;
            }else{
                so[i][j]={min(wall-1,i+k),j};
            }
        }
    }
    queue<tuple<int,int,int,int>> q;
    vector<vector<array<bool,2>>> vis(n,vector<array<bool,2>>(m,{false,false}));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='S'){
                q.emplace(i,j,1,0);
                vis[i][j][1]=true;
            }
        }
    }
    array<int,4> dx{0,0,1,-1},dy{1,-1,0,0};
    while(!q.empty()){
        auto [i,j,s,d]=q.front();
        q.pop();
        if(a[i][j]=='E'){
            cout << d << "\n";
            return;
        }
        if(s){
            for(auto [x,y]:{no[i][j],so[i][j],ea[i][j],we[i][j]}){
                int t=(query(i,j,x,y)-(a[i][j]=='*'?1:0)>0);
                if(!vis[x][y][t]){
                    vis[x][y][t]=true;
                    q.emplace(x,y,t,d+1);
                }
            }
        }
        for(int dir=0;dir<4;dir++){
            int x=i+dx[dir],y=j+dy[dir];
            int t=s;
            if(a[x][y]=='*')t=1;
            if(vis[x][y][t]||a[x][y]=='#')continue;
            vis[x][y][t]=true;
            q.emplace(x,y,t,d+1);
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}