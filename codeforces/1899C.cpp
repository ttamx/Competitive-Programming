#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2),qs(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    deque<int> dq;
    int ans=-1e9;
    dq.emplace_back(0);
    for(int i=1;i<=n;i++){
        if(i>0&&(a[i]+a[i-1])%2==0){
            dq.clear();
            dq.emplace_back(i-1);
        }
        if(!dq.empty())ans=max(ans,qs[i]-qs[dq.front()]);
        while(!dq.empty()&&qs[dq.back()]>=qs[i])dq.pop_back();
        dq.emplace_back(i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}