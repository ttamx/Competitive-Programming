#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N];

bool solve(int l,int r,int vl,int vr){
    if(l==r)return true;
    int pre=0,suf=0;
    for(int s=0;s<r-l;s++){
        pre=max(pre,a[l+s]);
        suf=max(suf,a[r-s]);
        if(pre==vl+s){
            return solve(l,l+s,vl,vl+s)&&solve(l+s+1,r,vl+s+1,vr);
        }
        if(suf==vl+s){
            return solve(r-s,r,vl,vl+s)&&solve(l,r-s-1,vl+s+1,vr);
        }
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }
        cout << (solve(1,n,1,n)?"Yes":"No") << "\n";
    }
}