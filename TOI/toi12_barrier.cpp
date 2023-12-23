#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,int> p2;

const int N=6e6+5;

int n,k;
int a[N];
ll qs[N];
deque<p2> dq;
p2 ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    dq.emplace_back(0,0);
    k++;
    for(int i=1;i<=n;i++){
        while(!dq.empty()&&i-dq.front().second+1>k)dq.pop_front();
        while(!dq.empty()&&dq.back().first>=qs[i])dq.pop_back();
        dq.emplace_back(qs[i],i);
        p2 res(qs[i]-dq.front().first,-(i-dq.front().second));
        ans=max(ans,res);
    }
    cout << ans.first << "\n" << -ans.second;
}