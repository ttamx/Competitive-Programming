#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,m;
ll cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=N-2;i>=0;i--)cnt[i]+=cnt[i+1];
    for(int i=1;i<=m;i++){
        ll ans=0;
        for(int j=i;j<N;j+=i)ans+=cnt[j];
        cout << ans << "\n";
    }
}