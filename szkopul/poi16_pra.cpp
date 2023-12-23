#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;
const int mod=1e9+7;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int n;
int a[N];
ll ans=0;
ll res=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        int left=n-i;
        res+=a[i]-1-f.read(a[i]);
        f.add(a[i],1);
        if(left%2==0){
            ans+=res;
            ans%=mod;
        }
        res*=left;
        res%=mod;
    }
    cout << ans;
}