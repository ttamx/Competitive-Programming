#include "aliens.h"
#include<bits/stdc++.h>

using namespace std;

long long take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
    vector<vector<int>> gr(m,vector<int>(m));
    for(int i=0;i<n;i++){
        int x=r[i],y=c[i];
        int a=min(x,y),b=max(x,y);
        gr[a][a]++;
        if(b+1<m)gr[b+1][a]--,gr[a][b+1]--,gr[b+1][b+1]++;
    }
    int ans=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i>0)gr[i][j]+=gr[i-1][j];
            if(j>0)gr[i][j]+=gr[i][j-1];
            if(i>0&&j>0)gr[i][j]-=gr[i-1][j-1];
            ans+=(gr[i][j]>0);
        }
    }
    return ans;
}
