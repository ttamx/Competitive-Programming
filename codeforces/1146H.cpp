#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = complex<ll>;

ll cross(P a,P b){
    return imag(conj(a)*b);
}

int is_upper(P a){
    return imag(a)>0||(imag(a)==0&&real(a)>0);
}

int cmp(P a,P b){
    int u=is_upper(a),v=is_upper(b);
    if(u!=v)return u>v;
    return cross(a,b)>0;
}

const int N=305;

int n;
P a[N];
ll dp[N][N][6];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a[i]=P(x,y);
    }
    vector<tuple<P,int,int>> vec;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j){
                vec.emplace_back(a[j]-a[i],i,j);
            }
        }
    }
    sort(vec.begin(),vec.end(),[&](auto x,auto y){
        return cmp(get<0>(x),get<0>(y));
    });
    for(int i=0;i<n;i++)dp[i][i][0]=1;
    for(auto &[_,i,j]:vec){
        for(int s=0;s<n;s++){
            for(int k=1;k<6;k++){
                dp[s][j][k]+=dp[s][i][k-1];
            }
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++)ans+=dp[i][i][5];
    cout << ans << "\n";
}