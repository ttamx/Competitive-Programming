#include<bits/stdc++.h>

using namespace std;

const int N=1<<20;

int n;
int a[N],b[N];
int pos[N];
int ans=0;

void dnc(int l,int r){
    if(l==r){
        if(a[l]!=b[l])cout << -1,exit(0);
        return;
    }
    int m=(l+r)/2;
    bool rev=false;
    for(int i=l;i<=m;i++)if(pos[a[i]]>m)rev=true;
    for(int i=m+1;i<=r;i++)if(pos[a[i]]<=m)rev=true;
    if(rev){
        reverse(a+l,a+r+1);
        ans++;
    }
    dnc(l,m);
    dnc(m+1,r);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    n=1<<n;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<n;i++)cin >> b[i];
    for(int i=0;i<n;i++)pos[b[i]]=i;
    dnc(0,n-1);
    cout << ans;
}