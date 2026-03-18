#include<bits/stdc++.h>

using namespace std;

const int N=5005;

const int INF=1e9;

struct DS{
    vector<pair<int,int>> dat;
    void init(){
        dat.clear();
    }
    void push(int i,int v){
        while(!dat.empty()&&dat.back().second<=v){
            dat.pop_back();
        }
        dat.emplace_back(i,v);
    }
    int query(int i){
        auto it=lower_bound(dat.begin(),dat.end(),make_pair(i,INT_MIN));
        assert(it!=dat.end());
        return it->second;
    }
}ds[N];

int lim[N];
int dp[N][N];

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int x=0,y=0,sx=0,sy=0;
    for(auto c:s){
        if(c=='U')x--;
        else if(c=='D')x++;
        else if(c=='L')y--;
        else if(c=='R')y++;
        sx=min(sx,x);
        sy=min(sy,y);
    }
    x=-sx,y=-sy;
    map<pair<int,int>,int> a;
    a[{x,y}]=0;
    lim[0]=1;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='U')x--;
        else if(s[i-1]=='D')x++;
        else if(s[i-1]=='L')y--;
        else if(s[i-1]=='R')y++;
        if(!a.count({x,y}))a[{x,y}]=-1;
        lim[i]=min(lim[i-1]+1,i-a[{x,y}]);
        a[{x,y}]=i;
    }
    for(int i=n-1;i>=0;i--)lim[i]=min(lim[i],lim[i+1]);
    x=-sx,y=-sy;
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            dp[i][j]=-INF;
        }
    }
    for(int i=0;i<=n+1;i++){
        ds[i].init();
    }
    dp[0][1]=0;
    a.clear();
    a[{x,y}]=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='U')x--;
        else if(s[i-1]=='D')x++;
        else if(s[i-1]=='L')y--;
        else if(s[i-1]=='R')y++;
        if(!a.count({x,y}))a[{x,y}]=-1;
        int t=a[{x,y}];
        for(int j=0;j<=lim[i-1];j++){
            ds[j].push(i-1,dp[i-1][j]);
        }
        for(int j=0;j+1<=lim[i];j++){
            dp[i][j+1]=ds[j].query(t+j)-i;
        }
        a[{x,y}]=i;
    }
    int ans=0;
    for(int j=0;j<=n+1;j++){
        for(int k=0;k<=lim[n];k++){
            ans=max(ans,dp[j][k]+k*(n+1));
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}