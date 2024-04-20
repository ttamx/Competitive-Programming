#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,k;
int a[N];
vector<pair<int,int>> stick;
int s;
int ans,ans2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    stick.resize(k);
    for(auto &[h,p]:stick)cin >> p >> h;
    cin >> s;
    sort(stick.rbegin(),stick.rend());
    for(auto [h,p]:stick)swap(a[p],a[p+1]);
    ans=a[s],ans2=max(a[s-1],a[s+1]);
    reverse(stick.begin(),stick.end());
    for(auto [h,p]:stick){
        swap(a[p],a[p+1]);
        if(s==p)s=p+1;
        else if(s==p+1)s=p;
        ans2=max({ans2,a[s-1],a[s+1]});
    }
    cout << max(ans,ans2) << "\n";
    cout << (ans>ans2?"NO":"USE");
}