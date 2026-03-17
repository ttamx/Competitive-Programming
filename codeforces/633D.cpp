#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1005;

int n;
ll a[N];
map<int,int> cnt;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cnt[a[i]]++;
    }
    int ans=2;
    ans=max(ans,cnt[0]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j||(a[i]==0&&a[j]==0))continue;
            vector<ll> b{a[i],a[j]};
            cnt[a[i]]--,cnt[a[j]]--;
            for(int i=0;;i++){
                ll v=b[i]+b[i+1];
                if(!cnt.count(v)||cnt[v]==0){
                    break;
                }
                cnt[v]--;
                b.emplace_back(v);
            }
            ans=max(ans,(int)b.size());
            for(auto x:b){
                cnt[x]++;
            }
        }
    }
    cout << ans << "\n";
}