#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(2*n);
    for(auto &x:a)cin >> x;
    long long ans=0;
    for(auto x:a)ans+=llabs(x);
    if(n==1){
        ans=min(ans,llabs(a[0]-a[1]));
    }
    if(n==2){
        long long res=0;
        for(auto x:a)res+=llabs(x-2);
        ans=min(ans,res);
    }
    if(n%2==0){
        long long sum=0,mn=1e18;
        for(auto x:a){
            sum+=llabs(x+1);
            if(llabs(x-n)-llabs(x+1)<mn){
                mn=llabs(x-n)-llabs(x+1);
            }
        }
        ans=min(ans,sum+mn);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}