#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

const int N=5e5+5;
const int D=10005;

int n,m,d;
int a[D][D],b[D][D],x[D],y[D];
int ans;
vector<pair<int,int>> vn,vm;

bool check(int i,int j,int k,int l){
    return (a[i][j]-a[i][l-1]-a[k-1][j]+a[k-1][l-1]==n)&&(x[i]-x[k-1]+y[j]-y[l-1]-(b[i][j]-b[i][l-1]-b[k-1][j]+b[k-1][l-1])==m);
}

bool chk(int i,int k){
    if(!check(i,d,k,1))return false;
    bool res=false;
    int l=1;
    for(int j=d+1;j<=2*d;j++){
        if(l<=j-d)l++;
        while(check(i,j,k,l+1))l++;
        ans=min(ans,(i-k+1)*(j-l+1));
        res=true;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> d;
    vn.resize(n);
    vm.resize(m);
    for(auto &[u,v]:vn)cin >> u >> v,u++,v++;
    for(auto &[u,v]:vm)cin >> u >> v,u++,v++;
    ans=d*d;
    auto sol=[&](){
        for(auto [u,v]:vn){
            a[u][v]++;
            a[u][v+d]++;
            a[u+d][v]++;
            a[u+d][v+d]++;
        }
        for(auto [u,v]:vm){
            b[u][v]++;
            b[u][v+d]++;
            b[u+d][v]++;
            b[u+d][v+d]++;
            x[u]++;
            y[v]++;
            x[u+d]++;
            y[v+d]++;
        }
        for(int i=1;i<=2*d;i++){
            for(int j=1;j<=2*d;j++){
                a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
                b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
            }
        }
        for(int i=1;i<=2*d;i++){
            x[i]+=x[i-1];
            y[i]+=y[i-1];
        }
        int k=1;
        for(int i=d+1;i<=2*d;i++){
            if(k<=i-d){
                k++;
                if(!check(i,d,k+1,1))continue;
            }
            while(check(i,d,k+1,1))k++;
            chk(i,k);
        }
    };
    sol();
    for(int i=1;i<=2*d;i++){
        x[i]=y[i]=0;
        for(int j=1;j<=2*d;j++)a[i][j]=b[i][j]=0;
    }
    for(auto &[u,v]:vn)swap(u,v);
    for(auto &[u,v]:vm)swap(u,v);
    sol();
    cout << ans;
}