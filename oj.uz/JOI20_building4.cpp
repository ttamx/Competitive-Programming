#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
int a[N][2];
int l[N][2],r[N][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=2*n;i++)cin >> a[i][0];
    for(int i=1;i<=2*n;i++)cin >> a[i][1];
    for(int i=1;i<=2*n;i++){
        l[i][0]=l[i][1]=N;
        r[i][0]=r[i][1]=-N;
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(a[i-1][j]<=a[i][k]){
                    l[i][k]=min(l[i][k],l[i-1][j]+(k?-1:1));
                    r[i][k]=max(r[i][k],r[i-1][j]+(k?-1:1));
                }
            }
        }
    }
    for(int x=0;x<2;x++){
        if(l[2*n][x]<=0&&0<=r[2*n][x]){
            int v=0;
            string ans="";
            for(int i=2*n;i>=1;i--){
                v-=(x?-1:1);
                ans.push_back("AB"[x]);
                for(int j=0;j<2;j++){
                    if(a[i][x]>=a[i-1][j]&&l[i-1][j]<=v&&v<=r[i-1][j]){
                        x=j;
                        break;
                    }
                }
            }
            reverse(ans.begin(),ans.end());
            cout << ans << "\n";
            exit(0);
        }
    }
    cout << -1 << "\n";
}