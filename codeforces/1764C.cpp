#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[x]++;
    }
    int sum=0;
    long long ans=0;
    for(auto [num,cnt]:mp){
        long long l=sum;
        long long r=n-sum-cnt;
        ans=max(ans,(l*r)+max(l,r)*cnt);
        sum+=cnt;
    }
    cout << max(2ll,ans) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}