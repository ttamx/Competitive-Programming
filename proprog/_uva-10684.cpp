#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    while(cin >> n){
        if(n==0)return 0;
        vector<long long> a(n+1),qs(n+1);
        for(int i=1;i<=n;i++)cin >> a[i],qs[i]=qs[i-1]+a[i];
        deque<long long> dq;
        long long ans=0;
        dq.emplace_back(0);
        for(int i=1;i<=n;i++){
            while(!dq.empty()&&dq.back()>=qs[i])dq.pop_back();
            dq.emplace_back(qs[i]);
            ans=max(ans,qs[i]-dq.front());
        }
        if(ans)cout << "The maximum winning streak is " << ans << ".\n";
        else cout << "Losing streak.\n";
    }
}