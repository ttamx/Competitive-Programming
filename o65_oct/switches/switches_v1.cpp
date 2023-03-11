#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

struct range{
    int r,l,c;
    bool operator<(const range &o){
        if(r!=o.r)return r<o.r;
        if(l!=o.l)return l<o.l;
        return c<o.c;
    }
};

int n,m,k;
int a[N];
ll qs[N],dp[25][N],dp2[25][N];
vector<range> v;

long long minimum_energy(int N, int M, int K,vector<int> A,vector<int> L,vector<int> R,vector<int> C){
    n=N,m=M,k=K;
    for(int i=0;i<n;i++)a[i+1]=A[i];
    for(int i=1;i<=n+1;i++)qs[i]=qs[i-1]+a[i];
    v.push_back({0,0,0});
    v.push_back({n+1,n+1,0});
    for(int i=0;i<m;i++)v.push_back({R[i]+1,L[i]+1,C[i]});
    sort(v.begin(),v.end(),[](const range &a,const range &b){
        if(a.r!=b.r)return a.r<b.r;
        if(a.l!=b.l)return a.l<b.l;
        return a.c<b.c;
    });
    for(int i=1;i<=m+1;i++){
        ll cost,kcost;
        if(v[i].l>v[i-1].r){
            cost=v[i].c+qs[v[i].l-1]-qs[v[i-1].r];
            kcost=v[i].c+abs(a[v[i].l]*a[v[i].l]-a[v[i-1].r]*a[v[i-1].r]);
        }else{
            cost=v[i].c+llabs(qs[v[i-1].r-1]-qs[v[i].l]);
            kcost=v[i].c+llabs(a[v[i].l]*a[v[i].l]-a[v[i-1].r]*a[v[i-1].r]);
        }
        cost=min(cost,qs[v[i].r]-qs[v[i-1].r]);
        kcost=min(kcost,llabs(a[v[i].r]*a[v[i].r]-a[v[i-1].r+1]*a[v[i-1].r+1]));
        for(int j=0;j<=k;j++)dp[j][i]=dp[j][i-1]+cost;
        for(int j=1;j<=k;j++)dp[j][i]=min(dp[j][i],dp[j-1][i-1]+kcost);
        cout << i << '\n';
        cout << v[i].l << ' ' << v[i].r << ' ' << v[i].c << '\n';
        cout << cost << ' ' << kcost << '\n';
        for(int j=0;j<=k;j++)cout << dp[j][i] << ' ';
        cout << "\n------------\n";
    }
    sort(v.begin(),v.end(),[](const range &a,const range &b){
        if(a.l!=b.l)return a.l>b.l;
        if(a.r!=b.r)return a.r>b.r;
        return a.c<b.c;
    });
    for(int i=1;i<=m+1;i++){
        ll cost,kcost;
        if(v[i].r>v[i-1].l){
            cost=v[i].c+qs[v[i].r-1]-qs[v[i-1].l];
            kcost=v[i].c+abs(a[v[i].r]*a[v[i].r]-a[v[i-1].l]*a[v[i-1].l]);
        }else{
            cost=v[i].c+llabs(qs[v[i-1].l-1]-qs[v[i].r]);
            kcost=v[i].c+llabs(a[v[i].r]*a[v[i].r]-a[v[i-1].l]*a[v[i-1].l]);
        }
        cost=min(cost,qs[v[i-1].l-1]-qs[v[i].l-1]);
        kcost=min(kcost,llabs(a[v[i].l]*a[v[i].l]-a[v[i-1].l-1]*a[v[i-1].l-1]));
        for(int j=0;j<=k;j++)dp2[j][i]=dp2[j][i-1]+cost;
        for(int j=1;j<=k;j++)dp2[j][i]=min(dp2[j][i],dp2[j-1][i-1]+kcost);
        cout << i << '\n';
        cout << v[i].l << ' ' << v[i].r << ' ' << v[i].c << '\n';
        cout << cost << ' ' << kcost << '\n';
        for(int j=0;j<=k;j++)cout << dp2[j][i] << ' ';
        cout << "\n------------\n";
    }
	return min(dp[k][m+1],dp2[k][m+1]);
}
