#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,k;
int a[N];

bool chk(int val){
    int sum=0,cnt=0;
    multiset<int> ms;
    for(int i=1;i<=n;i++){
        ms.emplace(a[i]);
        sum+=a[i];
        if(ms.size()>k)sum-=*ms.begin(),ms.erase(ms.begin());
        if(sum>=val&&ms.size()==k){
            if(++cnt>=m)return true;
            ms.clear();
            sum=0;
        }
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    int l=1,r=2e9;
    while(l<r){
        int mid=(1ll+l+r)/2;
        if(chk(mid))l=mid;
        else r=mid-1;
    }
    cout << l;
}