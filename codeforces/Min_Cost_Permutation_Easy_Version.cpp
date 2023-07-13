#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    if(n==1)return void(cout << a[1] << "\n");
    bool flip=false;
    if(c<0){
        flip=true;
        c=-c;
    }
    a[n+1]=1e9;
    sort(a.begin()+1,a.end());
    vector<vector<vector<ll>>> dp(n+2,vector<vector<ll>>(n+2,vector<ll>(4,1e18)));
    dp[1][1][0]=a[2]-a[1];
    dp[1][1][1]=0;
    dp[1][1][2]=0;
    for(int i=2;i<=n;i++){
        ll d=a[i]-a[i-1];
        for(int j=1;j<i;j++){
            dp[i][j][0]=min(dp[i][j][0],dp[i-1][j][0]+c+d);
            dp[i][i][0]=min(dp[i][i][0],dp[i-1][j][0]+d+abs(a[j]+c-a[i]));
            dp[i][j][1]=min(dp[i][j][1],dp[i-1][j][1]+c+d);
            dp[i][i][1]=min(dp[i][j][1],dp[i-1][j][0]+d+abs(a[j]+c-a[i]));
            dp[i][j][2]=min(dp[i][j][2],dp[i-1][j][0]+c+d);
            dp[i][j][2]=min(dp[i][j][2],dp[i-1][j][2]+c);
            dp[i][i][2]=min(dp[i][i][2],dp[i-1][j][2]+abs(a[j]+c-a[i]));
            dp[i][j][3]=min(dp[i][j][3],dp[i-1][j][3]+c);
            dp[i][j][3]=min(dp[i][j][3],dp[i-1][j][1]+c+d);
            dp[i][i][3]=min(dp[i][i][3],dp[i-1][j][2]+abs(a[j]+c-a[i]));
        }
    }
    pair<ll,ll> best(1e18,-1);
    for(int i=1;i<=n;i++)best=min(best,{dp[n][i][3],i});
    deque<ll> ans;
    function<void(int,int,int)> sol=[&](int i,int j,int k){
        ll res=dp[i][j][k];
        if(i==1)return void(ans.emplace_back(a[1]));
        ll d=a[i]-a[i-1];
        if(!flip){
            if(k==0){
                if(i==j)for(int j=i-1;j>=0;j--)if(res==dp[i-1][j][0]+d+abs(a[j]+c-a[i])){
                    sol(i-1,j,0);
                    ans.emplace_back(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][0]+c+d){
                    sol(i-1,j,0);
                    ll tmp=ans.back();
                    ans.pop_back();
                    ans.emplace_back(a[i]);
                    ans.emplace_back(tmp);
                    return;
                }
            }
            if(k==1){
                if(i==j)for(int j=i-1;j>=0;j--)if(res==dp[i-1][j][0]+d+abs(a[j]+c-a[i])){
                    sol(i-1,j,0);
                    ans.emplace_back(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][1]+c+d){
                    sol(i-1,j,1);
                    ll tmp=ans.back();
                    ans.pop_back();
                    ans.emplace_back(a[i]);
                    ans.emplace_back(tmp);
                    return;
                }
            }
            if(k==2){
                if(i==j)for(int j=i-1;j>=0;j--)if(res==dp[i-1][j][2]+abs(a[j]+c-a[i])){
                    sol(i-1,j,2);
                    ans.emplace_back(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][2]+c){
                    sol(i-1,j,2);
                    ll tmp=ans.back();
                    ans.pop_back();
                    ans.emplace_back(a[i]);
                    ans.emplace_back(tmp);
                    return;
                }
                if(j<i&&res==dp[i-1][j][0]+c+d){
                    sol(i-1,j,0);
                    ans.emplace_front(a[i]);
                    return;
                }
            }
            if(k==3){
                if(i==j)for(int j=i-1;j>=0;j--)if(res==dp[i-1][j][2]+abs(a[j]+c-a[i])){
                    sol(i-1,j,2);
                    ans.emplace_back(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][3]+c){
                    sol(i-1,j,3);
                    ll tmp=ans.back();
                    ans.pop_back();
                    ans.emplace_back(a[i]);
                    ans.emplace_back(tmp);
                    return;
                }
                if(j<i&&res==dp[i-1][j][1]+c+d){
                    sol(i-1,j,2);
                    ans.emplace_front(a[i]);
                    return;
                }
            }
        }else{
            if(k==0){
                if(j<i&&res==dp[i-1][j][0]+c+d){
                    sol(i-1,j,0);
                    ll tmp=ans.front();
                    ans.pop_front();
                    ans.emplace_front(a[i]);
                    ans.emplace_front(tmp);
                    return;
                }
                if(i==j)for(int j=0;j<i;j++)if(res==dp[i-1][j][0]+d+abs(a[j]+c-a[i])){
                    sol(i-1,j,0);
                    ans.emplace_back(a[i]);
                    return;
                }
            }
            if(k==1){
                if(j<i&&res==dp[i-1][j][1]+c+d){
                    sol(i-1,j,1);
                    ll tmp=ans.front();
                    ans.pop_front();
                    ans.emplace_front(a[i]);
                    ans.emplace_front(tmp);
                    return;
                }
                if(i==j)for(int j=0;j<i;j++)if(res==dp[i-1][j][0]+d+abs(a[j]+c-a[i])){
                    sol(i-1,j,0);
                    ans.emplace_back(a[i]);
                    return;
                }
            }
            if(k==2){
                if(j<i&&res==dp[i-1][j][0]+c+d){
                    sol(i-1,j,0);
                    ans.emplace_front(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][2]+c){
                    sol(i-1,j,2);
                    ll tmp=ans.front();
                    ans.pop_front();
                    ans.emplace_front(a[i]);
                    ans.emplace_front(tmp);
                    return;
                }
                if(i==j)for(int j=0;j<i;j++)if(res==dp[i-1][j][2]+abs(a[j]+c-a[i])){
                    sol(i-1,j,2);
                    ans.emplace_back(a[i]);
                    return;
                }
            }
            if(k==3){
                if(j<i&&res==dp[i-1][j][1]+c+d){
                    sol(i-1,j,2);
                    ans.emplace_front(a[i]);
                    return;
                }
                if(j<i&&res==dp[i-1][j][3]+c){
                    sol(i-1,j,3);
                    ll tmp=ans.front();
                    ans.pop_front();
                    ans.emplace_front(a[i]);
                    ans.emplace_front(tmp);
                    return;
                }
                if(i==j)for(int j=0;j<i;j++)if(res==dp[i-1][j][2]+abs(a[j]+c-a[i])){
                    sol(i-1,j,2);
                    ans.emplace_back(a[i]);
                    return;
                }
            }
        }
    };
    sol(n,best.second,3);
    if(flip)reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}