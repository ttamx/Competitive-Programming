#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
int a[N];
ll ans;

struct fenwick{
    ll t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f1,f2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        a[y]=x;
    }
    for(int i=n;i>=1;i--){
        ans+=f1.read(a[i])*a[i]+f2.read(a[i]);
        f1.add(a[i],1);
        f2.add(a[i],a[i]);
    }
    cout <<  ans;
}