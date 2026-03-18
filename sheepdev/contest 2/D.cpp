#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n=5,m=13;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    int d=-1,l=-1,r=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='D'){
                d=i;
                if(l==-1)l=j;
                r=j;
                a[i][j]='*';
            }else if(a[i][j]=='V'){
                a[i][j]='*';
            }
        }
    }
    int di=1,dj=1;
    assert(d!=-1);
    for(int t=0;t<1000;t++){
        for(int i=0;i<n;i++){
            string s="";
            for(int j=0;j<m;j++){
                if(i==d&&j>=l&&j<=r){
                    s.push_back("DV"[j*2==l+r]);
                }else{
                    s.push_back(a[i][j]);
                }
            }
            cout << s << "\n";
        }
        cout << "\n";
        if(r+dj>=m-1)dj=-dj;
        if(l+dj<=0)dj=-dj;
        if(d+di>=n-1)di=-di;
        if(d+di<=0)di=-di;
        d+=di,l+=dj,r+=dj;
    }
}