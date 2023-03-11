#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> v;
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        v.push_back(x);
        a.push_back({x,i});
    }
    sort(a.begin(),a.end());
    int cnt=0,sum=0;
    for(int i=0;i<n;i++){
        if(sum+a[i].first<=m)sum+=a[i].first,cnt++;
        else break;
    }
    if(cnt==n||v[cnt]>m){
        cout << n-cnt+1 << '\n';
        return;
    }
    sum=v[cnt];
    int cnt2=1;
    for(int i=0;i<n;i++){
        if(a[i].second==cnt)continue;
        if(sum+a[i].first<=m)sum+=a[i].first,cnt2++;
        else break;
    }
    if(cnt2==cnt)cout << n-cnt << '\n';
    else cout << n-cnt+1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}