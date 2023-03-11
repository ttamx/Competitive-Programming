#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.push_back({x,i+1});
    }
    sort(a.begin(),a.end());
    long long m=a[0].first;
    vector<pair<int,int>> ans;
    for(int i=1;i<n;i++){
        long long x=a[i].first;
        m=(x+m-1)/m*m;
        while(x<m){
            long long num=min(m-x,x);
            x+=num;
            ans.push_back({a[i].second,num});
        }
    }
    cout << ans.size() << '\n';
    for(auto [x,y]:ans)cout << x << ' ' << y << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}