#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n;
int a[N],h[N];

struct fenwick{
    ll t[N];
    void add(int i,ll v){
        while(i<N)t[i]=max(t[i],v),i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res=max(res,t[i]),i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)f.add(h[i],f.read(h[i])+a[i]);
    cout << f.read(n);
}