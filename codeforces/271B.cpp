#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

bool composite[N];
int nxt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    composite[0]=composite[1]=true;
    for(int i=2;i<N;i++){
        if(composite[i])continue;
        for(int j=i*2;j<N;j+=i)composite[j]=true;
    }
    for(int i=N-2;i>=0;i--){
        nxt[i]=composite[i]?nxt[i+1]:i;
    }
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
            x=nxt[x]-x;
        }
    }
    int ans=INT_MAX;
    for(int i=0;i<n;i++){
        int cur=0;
        for(int j=0;j<m;j++){
            cur+=a[i][j];
        }
        ans=min(ans,cur);
    }
    for(int i=0;i<m;i++){
        int cur=0;
        for(int j=0;j<n;j++){
            cur+=a[j][i];
        }
        ans=min(ans,cur);
    }
    cout << ans << "\n";
}