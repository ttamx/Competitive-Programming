#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n,k;
int a[3][N][N],b[3][N][N],dp1[3][N][N],dp2[3][N][N];
deque<pair<int,int>> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int m=0;m<3;++m){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cin >> a[m][i][j];
                a[m][i][j]+=a[m][i-1][j]+a[m][i][j-1]-a[m][i-1][j-1];
            }
        }
        for(int i=k;i<=n;++i){
            for(int j=k;j<=n;++j){
                b[m][i][j]=a[m][i][j]-a[m][i-k][j]-a[m][i][j-k]+a[m][i-k][j-k];
            }
        }
        for(int i=k;i<=n;++i){
            dq.clear();
            for(int j=k;j<=n;++j){
                while(!dq.empty()&&dq.front().second<=j-k)dq.pop_front();
                while(!dq.empty()&&dq.back().first<=b[m][i][j])dq.pop_back();
                dq.emplace_back(b[m][i][j],j);
                dp1[m][i][j]=dq.front().first;
            }
        }
        for(int i=k;i<=n;++i){
            dq.clear();
            for(int j=k;j<=n;++j){
                while(!dq.empty()&&dq.front().second<=j-k)dq.pop_front();
                while(!dq.empty()&&dq.back().first<=dp1[m][j][i])dq.pop_back();
                dq.emplace_back(dp1[m][j][i],j);
                dp2[m][j][i]=dq.front().first;
            }
        }
    }
    int ans=0;
    for(int i=k;i<=n;++i){
        for(int j=k;j<=n;++j){
            int tmp=0;
            for(int m=0;m<3;++m){
                tmp+=dp2[m][i][j];
            }
            ans=max(ans,tmp);
        }
    }
    cout << ans;
}