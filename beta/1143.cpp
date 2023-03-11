#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=200005;

int n,m,ans;
int mx[3];
int a[N][3];

void sol(int x,int y,int z){
    for(int i=1;i<=mx[x];i++){
        m=mx[y]*i;
        map<double,int> v;
        int c1=a[1][x]+a[1][y]*i;
        int x1=a[1][z];
        for(int j=2;j<=n;j++){
            int c2=a[j][x]+a[j][y]*i;
            int x2=a[j][z];
            double m2;
            if(x2!=x1){
                m2=1.0*(c1-c2)/(x2-x1);
                if(x2-x1<0){
                    if(m2<M){
                        v[m2]++;
                        v[M]--;
                    }
                }else{
                    if(0<m2){
                        v[0]++;
                        v[m2+1e-100]--;
                    }
                }
            }else if(c2<=c1){
                v[0]++;
                v[M]--;
            }
        }
        int res=0,num=0;
        for(auto [key,val]:v){
            num+=val;
            res=max(res,num);
        }
        ans=min(ans,n-res);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)for(int j=0;j<3;j++)cin >> a[i][j],mx[j]=max(mx[j],a[i][j]);
    for(int i=0;i<3;i++)mx[i]++;
    ans=n;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j)continue;
            for(int k=0;k<3;k++){
                if(i==k||j==k)continue;
                sol(i,j,k);
            }
        }
    }
    cout << ans;
}