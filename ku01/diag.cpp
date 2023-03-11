#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> x(n),y(n);
    vector<pair<int,int>> p;
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        x[i]=a+b;
        y[i]=a-b;
        p.push_back({x[i],y[i]});
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    pair<int,int> st;
    if(n&1)st={x[n/2],y[n/2]};
    else st={(x[n/2-1]+x[n/2])/2,(y[n/2-1]+y[n/2])/2};
    auto calc=[&](pair<int,int> x,pair<int,int> y){
        return abs(x.first-y.first)+abs(x.second-y.second);
    };
    long long ans=0;
    for(auto x:p)ans+=calc(st,x);
    cout << ans;
}