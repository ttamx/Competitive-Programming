#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    long long ans=0;
    map<pair<int,int>,int> mp;
    for(int i=0;i<n;i++){
        int a;
        cin >> a;
        int b=a;
        for(;b%2==0;b>>=1)a--;
        pair<int,int> res(a,b);
        ans+=mp[res]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}