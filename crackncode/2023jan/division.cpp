#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k=sqrt(5000000)+1;
    vector<bool> notprime(k);
    vector<int> prime;
    for(int i=2;i<k;i++){
        if(notprime[i])continue;
        prime.push_back(i);
        for(int j=i;j<k;j+=i)notprime[j]=true;
    }
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    long long ans=0;
    for(auto x:prime){
        int mx=0;
        for(auto &y:a){
            int cnt=0;
            while(y%x==0)y/=x,cnt++;
            mx=max(mx,cnt);
        }
        ans+=mx;
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    for(auto x:a)if(x>1)ans++;
    cout << ans;
}