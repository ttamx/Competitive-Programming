#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=305;
const ll INF=1e18;

int n;
ll m;
ll h[N],c[N];
ll dp[2][N][N];
ll aux[N][N];
map<ll,vector<int>> id;

void upd(ll &x,ll v){
    x=min(x,v);
}

void print(ll x){
    cerr << (x==INF?-1:x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> h[i] >> c[i];
        id[h[i]].emplace_back(i);
    }
    id[int(1e9)+n];
    int pre=1,cur=0;
    for(int j=0;j<=n;j++)for(int k=0;k<=n;k++)dp[0][j][k]=INF;
    ll tot=0,cnt=0;
    ll mn=INF;
    ll gr=0;
    for(auto [i,v]:id){
        swap(pre,cur);
        for(int j=0;j<=n;j++)for(int k=0;k<=n;k++)dp[cur][j][k]=INF;
        int s=v.size();
        cnt+=s;
        tot-=s*i;
        upd(dp[cur][cnt-1][1],(tot+cnt*i)*m);
        if(mn<INF){
            ll gap=i-gr;
            for(int j=0;j<=cnt;j++)for(int k=0;k<=cnt;k++)aux[j][k]=INF;
            for(int j=0;j<=cnt-s;j++)for(int k=1;k<=cnt-s;k++){
                ll lay=j/k;
                ll ext=0,lef=0;
                if(lay<gap){
                    ext+=lay*(lay+1)/2*m*k;
                    lef=j-lay*k;
                    if(lay<gap-1){
                        ext+=lef*(lay+1)*m;
                        lef=0;
                    }
                }else{
                    lay=gap-1;
                    ext+=lay*(lay+1)/2*m*k;
                    lef=j-lay*k;
                }
                ext+=lef*gap*m;
                if(lef+s<=k){
                    upd(dp[cur][0][k],dp[pre][j][k]+ext);
                    continue;
                }
                upd(aux[lef+s-k][k],dp[pre][j][k]+ext);
            }
            for(int j=cnt-1;j>=0;j--)for(int k=1;k<=cnt;k++)upd(aux[j][k],aux[j+1][k-1]+mn);
            for(int j=0;j<=cnt;j++)for(int k=0;k<=cnt;k++)upd(dp[cur][j][k],aux[j][k]);
        }
        if(mn<INF){
            ll gap=i-gr;
            for(int j=0;j<=cnt;j++)for(int k=0;k<=cnt;k++)aux[j][k]=INF;
            for(int j=0;j<=cnt-s;j++)for(int k=1;k<=cnt-s;k++){
                ll ext=j*gap*m;
                if(j+s<=k){
                    upd(dp[cur][0][k],dp[pre][j][k]+ext);
                    continue;
                }
                upd(aux[j+s-k][k],dp[pre][j][k]+ext);
            }
            for(int j=cnt-1;j>=0;j--)for(int k=1;k<=cnt;k++)upd(aux[j][k],aux[j+1][k-1]+mn);
            for(int j=0;j<=cnt;j++)for(int k=0;k<=cnt;k++)upd(dp[cur][j][k],aux[j][k]);
        }
        for(auto j:v)mn=min(mn,c[j]);
        gr=i;
    }
    ll ans=INF;
    for(int k=0;k<=n;k++)ans=min(ans,dp[cur][0][k]);
    cout << ans << "\n";
}