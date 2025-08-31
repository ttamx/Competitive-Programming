#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    auto b=a,c=a;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            a[i][j]=s[j]=='.';
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]){
                if(i>0&&a[i-1][j])b[i][j]++;
                if(j>0&&a[i][j-1])c[i][j]++;
            }
            if(i>0){
                b[i][j]+=b[i-1][j];
                c[i][j]+=c[i-1][j];
            }
            if(j>0){
                b[i][j]+=b[i][j-1];
                c[i][j]+=c[i][j-1];
            }
            if(i>0&&j>0){
                b[i][j]-=b[i-1][j-1];
                c[i][j]-=c[i-1][j-1];
            }
        }
    }
    auto query=[&](auto &&a,int l1,int l2,int r1,int r2){
        int res=a[r1][r2];
        if(l2)res-=a[r1][l2-1];
        if(l1)res-=a[l1-1][r2];
        if(l1&&l2)res+=a[l1-1][l2-1];
        return res;
    };
    int q;
    cin >> q;
    while(q--){
        int l1,r1,l2,r2;
        cin >> l1 >> l2 >> r1 >> r2;
        l1--,l2--,r1--,r2--;
        cout << query(b,l1+1,l2,r1,r2)+query(c,l1,l2+1,r1,r2) << "\n";
    }
}