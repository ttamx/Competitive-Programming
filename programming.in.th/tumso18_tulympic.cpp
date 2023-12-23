#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,x,t;
    cin >> n >> m >> x >> t;
    x--;
    vector<vector<pair<int,int>>> a(m,vector<pair<int,int>>(n));
    vector<pair<int,int>> p(n);
    vector<int> b(n);
    for(int i=0;i<n;i++)p[i].second=i;
    for(auto &x:b)cin >> x;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin >> a[j][i].first,a[j][i].second=i;
    for(int i=0;i<m;i++){
        sort(a[i].begin(),a[i].end());
        for(int j=0;j<n;j++)p[a[i][j].second].first+=b[j];
    }
    sort(p.begin(),p.end(),[&](pair<int,int> a,pair<int,int> b){
        if(a.first==b.first)return a.second<b.second;
        else return a.first>b.first;
    });
    int idx=0;
    while(idx<n&&p[idx].second!=x)idx++;
    cout << idx+1;
    if(t==2)cout << ' ' << p[idx].first;
}