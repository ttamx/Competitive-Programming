#include<bits/stdc++.h>

using namespace std;

const int N=200'005;
const int M=100'005;

int n,m;
int a[N];

bool check(int x){
    for(int v=0;v<=a[n];v++){
        bool ok=true;
        int used=v;
        for(int i=1;i<n;i++){
            int rem=x-used;
            if(rem<0){
                ok=false;
                break;
            }
            used=a[i]-rem;
        }
        if(ok&&used+a[n]-v<=x){
            return true;
        }
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        a[u]+=w;
        a[v]-=w;
        if(v<u)a[1]+=w;
    }
    for(int i=2;i<=n;i++)a[i]+=a[i-1];
    int l=0,r=m;
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout << l;
}