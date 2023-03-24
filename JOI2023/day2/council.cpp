#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int M=20;

int n,m;
int a[N][M],all[M],cur[M];
bool req[M];
int hsh[N],ans[N];
int mx[1<<M][2];
vector<int> vec[1<<M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            all[j]+=a[i][j];
            hsh[i]+=(a[i][j]<<j);
        }
        vec[hsh[i]].emplace_back(i);
    }
    for(int i=0;i<1<<m;i++){
        if(vec[i].size()==0)continue;
        int val=0;
        for(int j=0;j<m;j++){
            cur[j]=all[j]-((i>>j)&1);
            if(cur[j]>n/2)val++;
            req[j]=(cur[j]==n/2);
        }
        int res=0;
        for(int j=0;j<1<<m;j++){
            if(vec[j].size()==0)continue;
            if(j==i&&vec[j].size()==1)continue;
            int sum=0;
            for(int k=0;k<m;k++)if(req[k]&&((j>>k)&1)==0)sum++;
            res=max(res,sum);
        }
        for(auto j:vec[i])ans[j]=val+res;
    }
    for(int i=1;i<=n;i++)cout << ans[i] << '\n';
}