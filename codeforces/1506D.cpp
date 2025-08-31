#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<int,int> cnt;
    int mx=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mx=max(mx,++cnt[x]);
    }
    cout << max(n%2,2*mx-n) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}