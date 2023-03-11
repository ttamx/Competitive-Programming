#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2305;

int n;
ll ans=1;
ll dp[N][N];
vector<pair<ll,ll>> in;
vector<ll> a,b;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    in.resize(n);
    for(auto &[x,y]:in){
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(auto &[x,y]:in){
        x=lower_bound(a.begin(),a.end(),x)-a.begin()+1;
        y=lower_bound(b.begin(),b.end(),y)-b.begin()+1;
        dp[x][y]++;
    }
    for(int i=1;i<=a.size();i++){
        for(int j=1;j<=b.size();j++){
            dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            auto [a,b]=in[i];
            auto [c,d]=in[j];
            if(a>c)swap(a,c);
            if(b>d)swap(b,d);
            ans+=dp[c][d]-dp[a-1][d]-dp[c][b-1]+dp[a-1][b-1];
        }
    }
    cout << ans;
}