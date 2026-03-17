#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n,m;
    cin >> n >> m;
    if(n>3&&m>3)return void(cout << "-1\n");
    vector<vector<int>> a(n);
    for(auto &v:a){
        string s;
        cin >> s;
        for(auto x:s){
            v.emplace_back(x=='1');
        }
    }
    if(n<m){
        vector<vector<int>> b(m,vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                b[j][i]=a[i][j];
            }
        }
        swap(a,b);
        swap(n,m);
    }
    vector<int> b(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            b[i]|=a[i][j]<<j;
        }
    }
    vector<int> dp(1<<m);
    for(int i=0;i<(1<<m);i++)dp[i]=__builtin_popcount(b[0]^i);
    for(int i=1;i<n;i++){
        vector<int> ndp(1<<m,INF);
        for(int j=0;j<(1<<m);j++){
            for(int k=0;k<(1<<m);k++){
                bool ok=true;
                for(int x=3;x<(1<<m);x<<=1){
                    if(__builtin_popcount((j^k)&x)%2==0){
                        ok=false;
                    }
                }
                if(ok){
                    ndp[k]=min(ndp[k],dp[j]+__builtin_popcount(b[i]^k));
                }
            }
        }
        dp=move(ndp);
    }
    cout << *min_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}