#include<bits/stdc++.h>

using namespace std;

int n;
int a[20],b[20];

int sol(int costa,int costb,int numa,int numb){
    int idx=numa+numb;
    if(idx==n)return costa*(100-numa)+costb*(100-numb);
    idx++;
    return min(sol(costa+a[idx],costb,numa+1,numb),sol(costa,costb+b[idx],numa,numb+1));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i)cin >> a[i];
    for(int i=1;i<=n;++i)cin >> b[i];
    printf("%.2lf",sol(0,0,0,0)/100.0);
}