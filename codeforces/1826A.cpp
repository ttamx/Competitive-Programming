#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> cnt(n+1);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
    for(int i=n;i>=0;i--){
        if(cnt[i]+i==n){
            cout << i << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}