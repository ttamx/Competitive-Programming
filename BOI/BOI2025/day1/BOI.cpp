#include<bits/stdc++.h>

using namespace std;

const int N=2005;

int n;
int a[N][N];
int b[N];
vector<int> ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cin >> a[i][j];
        }
    }
    int mx=a[1][n];
    int st=1,cur=2;
    while(st<=n&&a[st+1][n]==mx)st++;
    b[st]=2;
    b[st+1]=1;
    while(st+2<=n){
        if(a[st][st+2]==1){
            b[st+2]=b[st]^b[st+1]^3;
        }else{
            b[st+2]=b[st];
        }
        st++;
    }
    vector<int> ans;
    for(int i=1;i<=n;i++)if(b[i]==2)ans.emplace_back(i);
    assert(ans.size()==mx);
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}