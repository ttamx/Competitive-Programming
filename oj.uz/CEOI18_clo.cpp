#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<int,int,int,int> t4;

const int N=2005;
const int C=1e5+5;
const ll inf=1e18;

int n,m;
vector<t4> a;
ll dp[C];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int c,f,v;
        cin >> c >> f >> v;
        a.emplace_back(f,1,c,v);
    }
    cin >> m;
    for(int i=0;i<m;i++){
        int c,f,v;
        cin >> c >> f >> v;
        a.emplace_back(f,0,c,v);
    }
    sort(a.rbegin(),a.rend());
    for(int i=1;i<C;i++)dp[i]=-inf;
    int sum=0;
    for(auto [f,t,c,v]:a){
        if(t){
            sum+=c;
            for(int i=sum;i>=c;i--)dp[i]=max(dp[i],dp[i-c]-v);
        }else{
            for(int i=0;i<=sum-c;i++)dp[i]=max(dp[i],dp[i+c]+v);
        }
    }
    ll ans=0;
    for(int i=0;i<=sum;i++)ans=max(ans,dp[i]);
    cout << ans;
}