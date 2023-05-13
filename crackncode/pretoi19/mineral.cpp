#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll k;
int a[N],b[N];

struct fenwick{
    int t[N];
    void init(){
        for(int i=0;i<N;i++)t[i]=0;
    }
    void add(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int read(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i],a[i]*=1000;
    for(int i=1;i<=n;i++)cin >> b[i];
    int l=0,r=1e7;
    while(l<r){
        int m=(l+r+1)/2;
        vector<ll> qs(n+1),vec(n+1);
        for(int i=1;i<=n;i++)vec[i]=qs[i]=qs[i-1]+a[i]-1ll*b[i]*m;
        sort(vec.begin(),vec.end());
        ll res=0;
        f.init();
        for(int i=0;i<=n;i++){
            int idx=lower_bound(vec.begin(),vec.end(),qs[i])-vec.begin()+1;
            res+=f.read(idx);
            f.add(idx,1);
        }
        if(res>=k)l=m;
        else r=m-1;
    }
    cout << fixed << setprecision(3) << l/1000.0;
}