#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<int,int> l,r;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(!l[x])l[x]=i;
        r[x]=i;
    }
    vector<int> vec;
    for(auto[x,y]:l)vec.emplace_back(y);
    sort(vec.begin(),vec.end());
    long long ans=0;
    for(auto [x,y]:r)ans+=upper_bound(vec.begin(),vec.end(),y)-vec.begin();
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}