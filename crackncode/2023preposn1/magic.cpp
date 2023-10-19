#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int cnt[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    k=max(k,1);
    vector<int> a(n);
    long long ans=0;
    for(auto &x:a)cin >> x;
    int d=0,id=0;;
    for(int i=0;i<n;i++){
        while(d<k&&id<n)d+=++cnt[a[id++]]==1;
        if(d==k)ans+=n-id+1;
        d-=--cnt[a[i]]==0;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}