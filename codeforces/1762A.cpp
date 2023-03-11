#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    int sum=0;
    int ans=32;
    for(auto &x:a){
        cin >> x;
        sum+=x;
        int cnt=0;
        if(x%2)while(x%2)x/=2,cnt++;
        else while(x%2==0)x/=2,cnt++;
        ans=min(ans,cnt);
    }
    if(sum%2==0)ans=0;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}