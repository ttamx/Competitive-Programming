#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const ll INF=1e18;

int n,m,k;
int a[N],f[N];
bool s[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++){
        int x;
        cin >> x;
        s[x]=true;
    }
    for(int i=1;i<=k;i++)cin >> a[i];
    if(s[0])cout << -1,exit(0);
    for(int i=1;i<n;i++)f[i]=s[i]?f[i-1]:i;
    ll ans=INF;
    for(int d=1;d<=k;d++){
        ll res=a[d];
        int p=0;
        for(int i=d;i<n;i+=d){
            i=f[i];
            if(i<=p){
                res=INF;
                break;
            }
            p=i;
            res+=a[d];
        }
        ans=min(ans,res);
    }
    cout << (ans<INF?ans:-1LL);
}