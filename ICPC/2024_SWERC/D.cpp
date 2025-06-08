#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x:a)cin >> x;
    vector<int> b(n,1e9);
    for(int t=0;t<2;t++){
        vector<int> s;
        for(int i=0;i<n;i++){
            while(!s.empty()&&a[s.back()]<a[i])s.pop_back();
            if(!s.empty())b[i]=min(b[i],i-s.back());
            s.emplace_back(i);
        }
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
    }
    long long ans=0;
    for(auto x:b)if(x<1e9)ans+=x;
    cout << ans << "\n";
}