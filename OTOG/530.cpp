#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=1e5+5;

int n,m;
int a[N],pos[N],qr[M];
bool del[N];
long long ans[M];
long long res;

struct fenwick2D{
    map<pair<int,int>,int> t;
    void add(int x,int y,int v){
        for(int i=x;i<N;i+=i&-i)for(int j=y;j<N;j+=j&-j)t[{i,j}]+=v;
    }
    int read(int x,int y){
        int res=0;
        for(int i=x;i>0;i-=i&-i)for(int j=y;j>0;j-=j&-j)res+=t[{i,j}];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
    for(int i=1;i<=m;i++){
        int x;
        cin >> x;
        qr[i]=pos[x];
        del[pos[x]]=true;
    }
    for(int i=1;i<=n;i++){
        if(del[i])continue;
        res+=f.read(n,i)-f.read(a[i],i);
        f.add(a[i],i,1);
    }
    for(int i=m;i>=1;i--){
        res+=f.read(n,qr[i])-f.read(a[qr[i]],qr[i])+f.read(a[qr[i]],n)-f.read(a[qr[i]],qr[i]);
        f.add(a[qr[i]],qr[i],1);
        ans[i]=res;
    }
    for(int i=1;i<=m;i++)cout << ans[i] << '\n';
}