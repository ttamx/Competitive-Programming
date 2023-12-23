#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b;
    cin >> a >> b;
    for(int i=1;i<=b;i++)for(int j=i;j<=b;j+=i)cnt[j]++;
    bool ok=false;
    for(int i=a;i<=b;i++)if(cnt[i]==3)cout << i << " ",ok=true;
    if(!ok)cout << -1;
}