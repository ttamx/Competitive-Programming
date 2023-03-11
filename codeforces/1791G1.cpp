#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,c;
    cin >> n >> c;
    vector<long long> v;
    for(int i=1;i<=n;i++){
        long long x;
        cin >> x;
        v.push_back(x+i);
    }
    sort(v.begin(),v.end());
    int ans=0;
    for(auto x:v){
        if(x<=c)c-=x,ans++;
        else break;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}