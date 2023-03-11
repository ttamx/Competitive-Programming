#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    long long ans=1ll*n*(n+1)/2;
    vector<int> cnt(4*n+1);
    int cur=0;
    cnt[0]=1;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cur^=x;
        for(int j=0;j*j<=2*n;j++)ans-=cnt[cur^(j*j)];
        cnt[cur]++;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    long long t;
    cin >> t;
    while(t--)runcase();   
}