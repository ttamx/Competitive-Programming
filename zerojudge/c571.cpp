#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int,int> t4;

const int N=1e5+5;

int n;
int ans[N];

struct point{
    int x,y,z,i;
    bool operator<(const point &o)const{
        return x>o.x||(x==o.x&&y<o.y);
    }
}a[N],b[N];

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<=n)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

void solve(int l,int r){
    if(l==r)return;
    int m=(l+r)/2;
    solve(l,m);
    solve(m+1,r);
    int id=l;
    for(int i=l,j=m+1;i<=m||j<=r;){
        if(j>r||(i<=m&&a[i].y>a[j].y)){
            b[id++]=a[i];
            f.add(a[i].z,1);
            i++;
        }else{
            b[id++]=a[j];
            ans[a[j].i]+=f.read(n)-f.read(a[j].z);
            j++;
        }
    }
    for(int i=l;i<=m;i++)f.add(a[i].z,-1);
    for(int i=l;i<=r;i++)a[i]=b[i];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i].x >> a[i].y >> a[i].z;
        a[i].i=i;
    }
    sort(a+1,a+n+1);
    solve(1,n);
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}