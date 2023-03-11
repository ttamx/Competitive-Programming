#include "compatibility.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll maximum_incompatibility(vector<vector<int>> a) {
    int n = a.size();
    int m = a[0].size();
    vector<ll> area(n);
    for(int i=0;i<n;i++)for(int j=1;j<m;j++)area[i]+=a[i][j-1]+a[i][j];
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int l=0,r=m-1;
            ll h=a[i][0]+a[j][m-1];
            while(l<r){
                int mid=(l+r)/2;
                int left=a[i][mid-1]+a[j][m-mid];
                int cur=a[i][mid]+a[j][m-mid-1];
                int right=a[i][mid+1]+a[j][m-mid-2];
                if(cur>=left&&cur>right)h=cur,l=mid,r=mid;
                else if(cur<=right)l=mid+1,h=right;
                else r=mid-1,h=left;
            }
            ll all=h*(m-1)*2;
            ans=max(ans,all-area[i]-area[j]);
        }
    }
    return ans;
}