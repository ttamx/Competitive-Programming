#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    long long sum=0;
    for(auto &x:a)cin >> x,sum+=x;
    long long ans=(sum+1)/2;
    sum/=2;
    sort(a.rbegin(),a.rend());
    for(auto x:a){
        if(sum<=0)break;
        sum-=x;
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}