#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
int pre[N],suf[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        suf[i]=pre[i]=x;
    }
    for(int i=1;i<=n;i++)pre[i]=max(pre[i],pre[i-1]);
    for(int i=n;i>=1;i--)suf[i]=max(suf[i],suf[i+1]);
    for(int i=2;i<=n;i++)cout << min(pre[i-1],suf[i]) << " \n"[i==n];
}