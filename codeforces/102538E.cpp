#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int LG=20;

int n;
int a[N];
int f[N],g[N],win[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x]^=1;
    }
    for(int i=1;i<=n;i++){
        g[i]=g[i-1]^a[i];
    }
    for(int i=1;i<N;i<<=1){
        for(int j=n;j>=0;j--){
            f[j]=(j+i*2<=n?f[j+i*2]:0);
            f[j]^=g[min(j+i*2-1,n)]^g[min(j+i-1,n)];
        }
        for(int x=1;x<=n;x++){
            int c=0;
            for(int j=0;j<=n;j+=x+1){
                int l=j,r=j+x+1;
                int rem=(l-r)&(i*2-1);
                c^=f[l];
                if(r+rem<=n)c^=f[r+rem];
                c^=g[min(r+rem-1,n)]^g[min(r+max(rem-i,0)-1,n)];
            }
            win[x]|=c;
        }
    }
    for(int i=1;i<=n;i++){
        cout << (win[i]?"Alice":"Bob") << " \n"[i==n];
    }
}