#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<vector<long long>> a(n,vector<long long>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    auto query=[&](int i1,int i2,int j1,int j2){
        long long res=1e9;
        for(int i=i1;i<=i2;i++){
            for(int j=j1;j<=j2;j++){
                res=min(res,a[i][j]);
            }
        }
        return res;
    };
    int m=n/2;
    long long ans=a[m][m];
    long long q1=query(0,m,0,m);
    long long q2=query(0,m,m,n-1);
    long long q3=query(m,n-1,0,m);
    long long q4=query(m,n-1,m,n-1);
    ans=min(ans,q1+q2+q3+q4);
    long long h1=min(q1+q2,query(0,m,m,m));
    long long h2=min(q3+q4,query(m,n-1,m,m));
    long long h3=min(q1+q3,query(m,m,0,m));
    long long h4=min(q2+q4,query(m,m,m,n-1));
    ans=min(ans,h1+h2);
    ans=min(ans,h3+h4);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}