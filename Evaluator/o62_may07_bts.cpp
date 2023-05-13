#include<bits/stdc++.h>

using namespace std;

const int N=3005;

int n,m,a,b;
int c[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> a >> b;
    if(a<b)swap(a,b);
    for(int i=1;i<n;i++)c[i]=2e9;
    for(int i=0;i<m;i++){
        int l,r,w;
        cin >> l >> r >> w;
        if(l>r)swap(l,r);
        r--;
        for(int j=l;j<=r;j++)c[j]=min(c[j],w-1);
    }
    int ans=0;
    for(int i=1;i<n;i++){
        if(c[i]>=a){
            ans+=a;
        }else if(c[i]>=b){
            ans+=b;
        }else{
            ans=-1;
            break;
        }
    }
    cout << ans;
}