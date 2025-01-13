#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector b(n,vector<int>(m)),c(n,vector<int>(m));
    for(int i=0;i<n;i++){
        int cur=0;
        for(int j=m-1;j>=0;j--){
            if(a[i][j]=='O'){
                cur++;
            }
            b[i][j]=cur;
        }
    }
    for(int i=0;i<m;i++){
        int cur=0;
        for(int j=n-1;j>=0;j--){
            if(a[j][i]=='I'){
                cur++;
            }
            c[j][i]=cur;
        }
    }
    int64_t ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='J'){
                ans+=1LL*b[i][j]*c[i][j];
            }
        }
    }
    cout << ans;
}