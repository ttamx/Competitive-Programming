#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    k=min(k,30);
    n=min(n,(1<<k)-1);
    long long ans=1;
    for(int i=0;i<k;i++)if((1<<i)&n)ans+=1<<i;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}