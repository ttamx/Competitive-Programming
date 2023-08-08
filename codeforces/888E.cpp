#include<bits/stdc++.h>

using namespace std;

const int N=40;

int n,m,k1,k2;
int a[N];
int ans;
vector<int> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)cin >> a[i],a[i]%=m;
    k1=n/2;
    k2=n-k1;
    for(int i=0;i<1<<k1;i++){
        int sum=0;
        for(int j=0;j<k1;j++){
            if(i>>j&1){
                sum+=a[j];
                if(sum>=m)sum-=m;
            }
        }
        v.emplace_back(sum);
    }
    v.emplace_back(0);
    sort(v.begin(),v.end());
    for(int i=0;i<1<<k2;i++){
        int sum=0;
        for(int j=0;j<k2;j++){
            if(i>>j&1){
                sum+=a[j+k1];
                if(sum>=m)sum-=m;
            }
        }
        ans=max(ans,sum+*prev(lower_bound(v.begin(),v.end(),m-sum)));
    }
    cout << ans << "\n";
}