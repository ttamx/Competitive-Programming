#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int LG=18;
const int INF=INT_MAX/2;

int n,m;
int l[N],r[N],vals[2*N];
int ans=INF;

struct Fenwick{
    int t[2*N];
    void update(int i,int v){
        for(;i<2*N;i+=i&-i)t[i]=max(t[i],v);
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res=max(res,t[i]);
        return res;
    }
}f[LG];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        vals[i*2-1]=l[i],vals[i*2]=r[i];
    }
    sort(vals+1,vals+2*n+1);
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(vals+1,vals+2*n+1,l[i])-vals;
        r[i]=lower_bound(vals+1,vals+2*n+1,r[i])-vals;
    }
    for(int i=1;i<=n;i++)if(l[i]<r[i])f[0].update(l[i],r[i]);
    for(int k=1;k<LG;k++){
        for(int i=1;i<=2*n;i++){
            f[k].update(i,f[k-1].query(f[k-1].query(i)));
        }
    }
    for(int i=1;i<=n;i++)if(r[i]<l[i]){
        int p=r[i],res=1;
        for(int j=LG-1;j>=0;j--){
            int x=f[j].query(p);
            if(x>=l[i])continue;
            p=x;
            res+=1<<j;
        }
        if(f[0].query(p)<l[i])continue;
        ans=min(ans,res+1);
    }
    cout << (ans==INF?-1:ans) << "\n";
}