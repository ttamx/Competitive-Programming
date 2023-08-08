#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<long long,int>> a(n);
    long long sum=0,sum2=0;
    int id=0;
    for(auto &[x,y]:a)cin >> x,sum+=x,y=id++;
    sort(a.begin(),a.end());
    vector<long long> ans(n,n);
    for(int i=0;i<n;i++){
        auto [x,y]=a[i];
        sum-=x;
        ans[y]+=sum-x*(n-i-1);
        ans[y]+=x*i-sum2;
        sum2+=x;
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}