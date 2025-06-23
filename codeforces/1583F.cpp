#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n,k;
int col;
int ans[N][N];

void rec(int l,int r,int c){
    col=max(col,c);
    if(r-l<k){
        for(int i=l;i<=r;i++){
            for(int j=l+1;j<=r;j++){
                ans[i][j]=c;
            }
        }
        return;
    }
    int s=(r-l)/k+1;
    for(int cl=l;cl<=r;cl+=s){
        int cr=min(cl+s-1,r);
        for(int i=l;i<cl;i++){
            for(int j=cl;j<=cr;j++){
                ans[i][j]=c;
            }
        }
        rec(cl,cr,c+1);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    rec(1,n,1);
    cout << col << "\n";
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            cout << ans[i][j] << " ";
        }
    }
    cout << "\n";
}